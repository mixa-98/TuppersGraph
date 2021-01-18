#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#define NUMBEROFROWS 17
#define NUMBEROFCOLS 106
#define PIXELPERCELL 8
typedef struct eventspoints{
    uint8_t points[NUMBEROFROWS][NUMBEROFCOLS];
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *windows;
    SDL_TimerID eventtimer;
    uint32_t leftbutd;
    uint32_t quit;
    uint32_t x;
    uint32_t y;
    uint8_t xlast;
    uint8_t ylast;
    uint8_t nu;
} t_eventspoints;

void renderlines(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    for(int i = 6; i < 846; i += 8)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, 134);
        SDL_RenderDrawLine(renderer, i + 1, 0, i + 1, 134);
    }
    for(int i = 6; i < 134; i += 8)
    {
        SDL_RenderDrawLine(renderer, 0, i, 846, i);
        SDL_RenderDrawLine(renderer, 0, i + 1, 846, i + 1);
    }
}


void init_uint16_t_mass(uint16_t **mass, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        *mass[i] = 0;
    }
}


uint16_t *multiplicationmass(uint16_t *mass, uint16_t len, uint16_t multiplicator)
{
    for(uint16_t i = 0; i < len; i++)
    {
        mass[i] *= multiplicator;
    }
    for(uint16_t i = 0; i < len; i++)
    {
        if(mass[i] > 10)
        {
            mass[i + 1] += mass[i] / 10;
            mass[i] %= 10;
        }
    }
    return mass;
}


void addmasses(uint16_t **mass, uint16_t *mass2, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        *mass[i] += mass2[i];
    }
    for(uint16_t i = 0; i < len; i++)
    {
        if(*mass[i] > 10)
        {
            *mass[i + 1] += *mass[i] / 10;
            *mass[i] %= 10;
        }
    }
}


uint16_t *calcpoints(uint8_t points[17][106], t_eventspoints *evp)
{
    evp->nu = 0;
    uint16_t *rslt = (uint16_t*)malloc(544 * sizeof(uint16_t));
    if(!rslt)
    {
        evp->quit = 1;
        return NULL;
    }
    uint16_t tempmasscounter = 0;
    uint16_t *rsltspecialcounter = (uint16_t*)malloc(543 * sizeof(uint16_t));
    if(!rsltspecialcounter)
    {
        evp->quit = 1;
        return NULL;
    }
    rsltspecialcounter[0] = 2;
    uint16_t *tempmass = (uint16_t*)malloc(544 * sizeof(uint16_t));
    if(!tempmass)
    {
        evp->quit = 1;
        return NULL;
    }
    for(uint8_t x = 0; x < NUMBEROFCOLS; x++)
    {
        for(uint8_t y = NUMBEROFROWS - 1; y + 1 != 0; y--)
        {
            tempmass[tempmasscounter] = points[x][y];
            tempmasscounter++;
        }
    }
    for (uint16_t i = 0; i < 544; i++)
    {
        addmasses(&rslt, multiplicationmass(rsltspecialcounter, 544, tempmass[i]), 544);
        rsltspecialcounter = multiplicationmass(rsltspecialcounter, 544, 2);
    }
    free(rsltspecialcounter);
    free(tempmass);
    return rslt;
}


void rendersquares(SDL_Renderer *renderer, uint8_t points[17][106])
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect rect;
    for(uint8_t y = 0; y < NUMBEROFROWS; y++)
    {
        for(uint8_t x = 0; x < NUMBEROFCOLS; x++)
        {
            rect.x = x*PIXELPERCELL;
            rect.y = y*PIXELPERCELL;
            rect.w = PIXELPERCELL - 2;
            rect.h = PIXELPERCELL - 2;
            if(points[y][x])
            {
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}


void initpoints(uint8_t points[NUMBEROFROWS][NUMBEROFCOLS])
{
    for(int y = 0; y < NUMBEROFROWS; y++)
    {
        for(int x = 0; x < NUMBEROFCOLS; x++)
        {
            points[y][x] = 0;
        }
    }
}


void printmass(uint16_t *mass, uint32_t masslen)
{
    for(uint32_t i = 0; i < masslen; i++)
    {
        char c = mass[i] + '0';
        write(1, &c, 1);
    }
    write(1, "\n", 1);
}


int main(void)
{
    t_eventspoints evp;
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        printf("%s\n", SDL_GetError());
        return 1;
    }
    evp.windows = SDL_CreateWindow("TuppersGraph", 100, 100, 846, 134, SDL_WINDOW_SHOWN);
    if(!evp.windows)
    {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    evp.renderer = SDL_CreateRenderer(evp.windows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!evp.renderer)
    {
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(evp.windows);
        SDL_Quit();
        return 1;
    }
    evp.xlast = NUMBEROFCOLS + 1;
    evp.ylast = NUMBEROFROWS + 1;
    evp.quit = 0;
    evp.leftbutd = 0;
    evp.nu = 0;
    initpoints(evp.points);
    while(!evp.quit)
    {
        while(SDL_PollEvent(&evp.event))
        {
            if(evp.event.type == SDL_MOUSEBUTTONUP && evp.event.button.button == SDL_BUTTON_LEFT && evp.leftbutd)
            {
                evp.leftbutd = 0;
            }
            if((evp.event.type == SDL_MOUSEBUTTONDOWN && evp.event.button.button == SDL_BUTTON_LEFT) || evp.leftbutd)
            {
                evp.leftbutd = 1;
                evp.y = evp.event.button.y;
                evp.x = evp.event.button.x;
                evp.x = evp.x/PIXELPERCELL;
                evp.y = evp.y/PIXELPERCELL;
                if(NUMBEROFCOLS > evp.x && NUMBEROFROWS > evp.y && (evp.xlast != evp.x || evp.ylast != evp.y))
                {
                    evp.points[evp.y][evp.x] = !evp.points[evp.y][evp.x];
                    evp.nu = 1;
                }
                evp.xlast = evp.x;
                evp.ylast = evp.y;
            }
            if(evp.event.type == SDL_QUIT)
            {
                evp.quit = 1;
            }
        }
        SDL_SetRenderDrawColor(evp.renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(evp.renderer);
        rendersquares(evp.renderer, evp.points);
        renderlines(evp.renderer);
        if(evp.nu)
        {
            uint16_t *pointcalc = calcpoints(evp.points, &evp);
            printmass(pointcalc, 544);
            free(pointcalc);
        }
        SDL_RenderPresent(evp.renderer);
    }
    SDL_DestroyRenderer(evp.renderer);
    SDL_DestroyWindow(evp.windows);
    SDL_RemoveTimer(evp.eventtimer);
    SDL_Quit();
    return 0;
}