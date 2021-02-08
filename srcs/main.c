#include "../mTupperGraph.h"


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


void init_uint16_t_mass(uint16_t *mass, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        mass[i] = 0;
    }
}


void massreverse(uint16_t *str, uint16_t len)
{
	uint16_t i = 0;
    while (i != len / 2)
	{
		uint16_t tmp = *(str + i);
		*(str + i) = *(str + (len - i - 1));
		*(str + (len - i - 1)) = tmp;
		i++;
	}
}

uint16_t *multiplicationmass(uint16_t *mass, uint16_t len, uint16_t lenofrslt, uint16_t multiplicator)
{
    uint16_t *rslt = (uint16_t*)malloc(lenofrslt * sizeof(uint16_t));
    for(uint16_t i = 0; i < len; i++)
    {
        rslt[i] = mass[i] * multiplicator;
    }
    for(uint16_t i = 0; i < lenofrslt; i++)
    {
        if(rslt[i] >= 10)
        {
            rslt[i + 1] += rslt[i] / 10;
            rslt[i] %= 10;
        }
    }
    return rslt;
}


uint16_t *dividemass(uint16_t *mass, uint16_t len, uint16_t divider)
{
    uint16_t *rslt = (uint16_t*)malloc(len * sizeof(uint16_t));
    if(rslt == NULL)
    {
        return NULL;
    }
    for(uint16_t i = len; i > 0; i--)
    {
        rslt[i] = mass[i] / divider;
        mass[i - 1] += ((mass[i] - rslt[i] * divider) * 10);
    }
    rslt[0] = mass[0] / divider;
    return rslt;
}


void addmasses(uint16_t *mass, uint16_t *mass2, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        mass[i] += mass2[i];
    }
    for(uint16_t i = 0; i < len; i++)
    {
        if(mass[i] >= 10)
        {
            mass[i + 1] += mass[i] / 10;
            mass[i] %= 10;
        }
    }
}


uint16_t *calcpoints(uint16_t points[17][106], t_eventspoints *evp)
{
    evp->nu = 0;
    uint16_t *rslt = (uint16_t*)malloc(544 * sizeof(uint16_t));
    if(!rslt)
    {
        evp->quit = 1;
        return NULL;
    }
    init_uint16_t_mass(rslt, 544);
    uint16_t tempmasscounter = 0;
    uint16_t *rsltspecialcounter = (uint16_t*)malloc(543 * sizeof(uint16_t));
    if(!rsltspecialcounter)
    {
        evp->quit = 1;
        return NULL;
    }
    init_uint16_t_mass(rsltspecialcounter, 543);
    rsltspecialcounter[0] = 2;
    uint16_t *tempmass = (uint16_t*)malloc(1802 * sizeof(uint16_t));
    if(!tempmass)
    {
        evp->quit = 1;
        return NULL;
    }
    init_uint16_t_mass(tempmass, 1802);
    for(uint16_t x = 0; x < NUMBEROFCOLS; x++)
    {
        for(int8_t y = NUMBEROFROWS - 1; y >= 0; y--)
        {
            tempmass[tempmasscounter] = points[y][x];
            tempmasscounter++;
        }
    }
    rslt[0] = tempmass[0]? 1 : 0;
    uint16_t *forfree;
    for (uint16_t i = 1; i < 1802; i++)
    {
        forfree = multiplicationmass(rsltspecialcounter, 543, 543, tempmass[i]);
        addmasses(rslt, forfree, 543);
        free(forfree);
        forfree = multiplicationmass(rsltspecialcounter, 543, 543, 2);
        free(rsltspecialcounter);
        rsltspecialcounter = forfree;
    }
    free(rsltspecialcounter);
    free(tempmass);
    uint16_t *rslt2 = multiplicationmass(rslt, 544, 544, 17);
    free(rslt);
    return rslt2;
}


void rendersquares(SDL_Renderer *renderer, uint16_t points[17][106])
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect rect;
    for(uint16_t y = 0; y < NUMBEROFROWS; y++)
    {
        for(uint16_t x = 0; x < NUMBEROFCOLS; x++)
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


void printpoints(uint16_t points[NUMBEROFROWS][NUMBEROFCOLS])
{
    for(uint16_t x = 0; x < NUMBEROFCOLS; x++)
    {
        for(int8_t y = NUMBEROFROWS - 1; y >= 0; y--)
        {
            printf("%u", (unsigned short)points[y][x]);
        }
    }
}


uint16_t f_strlen(char *str)
{
	int len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}


uint16_t *getmasszeros(uint16_t lenf)
{
    uint16_t *rslt = (uint16_t*)malloc(lenf * sizeof(uint16_t));
    init_uint16_t_mass(rslt, lenf);
    return rslt;
}


void f_strreverse(char *str)
{
	int len = f_strlen(str);
	int i = 0;
    while (i != len / 2)
	{
		char tmp = *(str + i);
		*(str + i) = *(str + (len - i - 1));
		*(str + (len - i - 1)) = tmp;
		i++;
	}
}


uint16_t *strtomassint(char *str, uint16_t lenf)
{
    f_strreverse(str);
    uint16_t *rslt = getmasszeros(lenf);
    for(uint16_t i = 0; str[i]; i++)
    {
        rslt[i] = str[i] - '0';
    }
    return rslt;
}


uint16_t ismassnenull(uint16_t *mass, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        if(mass[i] > 0)
        {
            return 1;
        }
    }
    return 0;
}


uint16_t ismassone(uint16_t *mass, uint16_t len)
{
    if(mass[0] != 1) return 0;
    for(uint16_t i = 1; i < len; i++)
    {
        if(mass[i] > 0)
        {
            return 0;
        }
    }
    return 1;
}


void rewritepoints(uint16_t points[NUMBEROFROWS][NUMBEROFCOLS], uint16_t *mass)
{
    uint16_t i = 0;
    for(uint16_t x = 0; x < NUMBEROFCOLS; x++)
    {
        for(int8_t y = NUMBEROFROWS - 1; y >= 0; y--, i++)
        {
            points[y][x] = mass[i];
        }
    }
}


void initpoints(uint16_t points[NUMBEROFROWS][NUMBEROFCOLS])
{
    for(int y = 0; y < NUMBEROFROWS; y++)
    {
        for(int x = 0; x < NUMBEROFCOLS; x++)
        {
            points[y][x] = 0;
        }
    }
}


uint16_t modmassby2(uint16_t *mass)
{
    return mass[0] % 2;
}


void calcpositions(uint16_t points[NUMBEROFROWS][NUMBEROFCOLS], uint16_t *mass)
{
    if(!ismassnenull(mass, 1802))return;
    uint16_t *newmass;
    uint16_t *oldmass = mass;
    newmass = dividemass(oldmass, 1802, 17);
    oldmass = newmass;
    uint16_t *rslt = (uint16_t*)malloc(1802 * sizeof(uint16_t));
    init_uint16_t_mass(rslt, 1802);
    uint16_t i = 0;
    for(; !ismassone(oldmass, 1802); i++)
    {
        rslt[i] = modmassby2(oldmass);
        newmass = dividemass(oldmass, 1802, 2);
        if(newmass == NULL)
        {
            free(oldmass);
            free(rslt);
            return;
        }
        printreversemass(newmass, 1802);
        printf("%u", (uint)i);
        free(oldmass);
        oldmass = newmass;
    }
    rslt[i]=modmassby2(oldmass);
    free(oldmass);
    rewritepoints(points, rslt);
    free(rslt);
}


int main(int argc, char *argv[])
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
    if(argc == 2)
    {
        uint16_t* startparam = strtomassint(argv[1], 1802);
        calcpositions(evp.points, startparam);
        free(startparam);
    }
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
                evp.y = evp.event.button.y;
                evp.x = evp.event.button.x;
                evp.x = evp.x/PIXELPERCELL;
                evp.y = evp.y/PIXELPERCELL;
                if(NUMBEROFCOLS > evp.x && NUMBEROFROWS > evp.y && ((evp.xlast != evp.x || evp.ylast != evp.y) || evp.leftbutd == 0))
                {
                    evp.points[evp.y][evp.x] = evp.points[evp.y][evp.x]? 0 : 1;
                    evp.nu = 1;
                    evp.xlast = evp.x;
                    evp.ylast = evp.y;
                }
                evp.leftbutd = 1;
            }
            if(evp.event.type == SDL_QUIT)
            {
                evp.quit = 1;
            }
            if(evp.event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
            {
                initpoints(evp.points);
            }
        }
        SDL_SetRenderDrawColor(evp.renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(evp.renderer);
        rendersquares(evp.renderer, evp.points);
        renderlines(evp.renderer);
        if(evp.nu)
        {
            uint16_t *pointcalc = calcpoints(evp.points, &evp);
            printreversemass(pointcalc, 544);
            free(pointcalc);
        }
        SDL_RenderPresent(evp.renderer);
    }
    SDL_DestroyRenderer(evp.renderer);
    SDL_DestroyWindow(evp.windows);
    SDL_Quit();
    return 0;
}