#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
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


uint16_t *calcpoints(uint8_t points[17][106], t_eventspoints *evp)
{
    evp->nu = 0;
    uint16_t calcpoint[] = {0, 0, 0, 0};
    uint16_t countpoints;
    uint16_t *rslt = (uint16_t*)malloc(451 * sizeof(uint16_t));
    if(!rslt)
    {
        evp->quit = 1;
        return NULL;
    }
    uint16_t rsltcounter;
    for(uint8_t x = 0; x < NUMBEROFCOLS; x++)
    {
        for(uint8_t y = NUMBEROFROWS - 1; y + 1 != 0; y--)
        {
            if(countpoints == 4)
            {
                countpoints = 0;
                if(calcpoint[0] == 0)
                {
                    if(calcpoint[1] == 0)
                    {
                        if(calcpoint[2] == 0)
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 0; //0000
                            }
                            else
                            {
                                rslt[rsltcounter] += 1; //0001
                            }
                        }
                        else
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 2; //0010
                            }
                            else
                            {
                                rslt[rsltcounter] += 3; //0011
                            }
                        }
                    }
                    else
                    {
                        if(calcpoint[2] == 0)
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 4; //0100
                            }
                            else
                            {
                                rslt[rsltcounter] += 5; //0101
                            }
                        }
                        else
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 6; //0110
                            }
                            else
                            {
                                rslt[rsltcounter] += 7; //0111
                            }
                        }
                    }
                }
                else
                {
                    if(calcpoint[1] == 0)
                    {
                        if(calcpoint[2] == 0)
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 8; //1000
                            }
                            else
                            {
                                rslt[rsltcounter] += 9; //1001
                                if(rslt[rsltcounter] == 10)
                                {
                                    rslt[rsltcounter + 1] = 1;
                                    rslt[rsltcounter] = 0;
                                }
                            }
                        }
                        else
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 0; //1010
                                rslt[rsltcounter + 1] += 1;
                            }
                            else
                            {
                                rslt[rsltcounter] += 1; //1011
                                rslt[rsltcounter + 1] += 1;
                            }
                        }
                    }
                    else
                    {
                        if(calcpoint[2] == 0)
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] += 3; //1100
                                rslt[rsltcounter + 1] += 1;
                            }
                            else
                            {
                                rslt[rsltcounter] += 4; //1101
                                rslt[rsltcounter + 1] += 1;
                            }
                        }
                        else
                        {
                            if(calcpoint[3] == 0)
                            {
                                rslt[rsltcounter] = 5; //1110
                                rslt[rsltcounter + 1] += 1;
                            }
                            else
                            {
                                rslt[rsltcounter] = 6; //1111
                                rslt[rsltcounter + 1] += 1;
                            }
                        }
                    }
                }
                rsltcounter++;
            }
            calcpoint[countpoints] = points[y][x];
            countpoints++;
        }
    }
    if(calcpoint[0] == 0)
    {
        if(calcpoint[1] == 0)
        {
            rslt[450] += 0; //00
        }
        else
        {
            rslt[450] += 1; //01
        }
    }
    else
    {
        if(calcpoint[1] == 0)
        {
            rslt[450] += 2; //10
        }
        else
        {
            rslt[450] += 3; //11
        }
    }
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
        printf("%d", mass[i]);
    }
    printf("\n");
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
            printmass(pointcalc, 451);
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