#ifndef MTUPPERGRAPH
# define MTUPPERGRAPH
# include <SDL2/SDL.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# define NUMBEROFROWS 17
# define NUMBEROFCOLS 106
# define PIXELPERCELL 8



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


uint16_t *multiplicationmass(uint16_t *mass, uint16_t len, uint16_t lenofrslt, uint16_t multiplicator);
uint16_t *strtomassint(char *str, uint16_t lenf);
uint16_t f_strlen(char *str);
uint16_t *getmasszeros(uint16_t lenf);
void f_massreverse(uint16_t *str, uint8_t len);
void renderlines(SDL_Renderer *renderer);
void printreversemass(uint16_t *mass, uint32_t masslen);
void init_uint16_t_mass(uint16_t *mass, uint16_t len);
uint16_t *dividemass(uint16_t *mass, uint16_t len, uint16_t lenofrslt, uint16_t divider);
void addmasses(uint16_t *mass, uint16_t *mass2, uint16_t len);
uint16_t *calcpoints(uint8_t points[17][106], t_eventspoints *evp);
void rendersquares(SDL_Renderer *renderer, uint8_t points[17][106]);
void initpoints(uint8_t points[NUMBEROFROWS][NUMBEROFCOLS]);
#endif
