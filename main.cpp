#include <SDL2/SDL.h>
#include <iostream>
#include <complex>
#include <string>

#define Width 1000
#define Height 1000

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init(SDL_INIT_VIDEO)\n";
        return -1;
    }


    SDL_Window *window = SDL_CreateWindow("MandelbrotSet",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Width, Height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_ARGB8888);

    double ratio = Width/Height;
    double Xm = -1; // window center coordinates
    double Ym = 0;
    double pictureWidth = 3;
    double pictureHeight = pictureWidth/ratio;

    int PaletteSize = 255;
    int palette[PaletteSize + 1][3];

    for (int i = 0; i <= PaletteSize; ++i)
    {
        palette[i][0] = i < 2 * PaletteSize / 3
        ? 255 * (4 * i) / PaletteSize
        : 0;

        palette[i][1] = 0;

        palette[i][2] = i < PaletteSize / 3
        ? 0
        : 255 * (PaletteSize - i) / PaletteSize;
    }
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
        std::complex<double> c(x*pictureWidth/Width + Xm - (pictureWidth/2),Ym + (pictureHeight/2) - y*pictureHeight/Height);
        std::complex<double> z(0.0, 0.0);
        int cnt = 0;
        while (cnt < PaletteSize)
        {
            z = z * z + c;
            if (abs(z) > 2.0)
            break;
            ++cnt;
        }
        SDL_SetRenderDrawColor(renderer, palette[cnt][0], palette[cnt][1], palette[cnt][2], 0xff);
        SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    /*
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
    std::string sciezka = ("/home/bartek/Programowanie/MandelbrotSet/output/" + std::to_string(i) + ".bmp");
    const char *c = sciezka.c_str();
    SDL_SaveBMP(surface, c);
    */
    SDL_RenderPresent(renderer);
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    //Cleaning

    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;//
}
