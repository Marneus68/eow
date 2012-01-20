#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "constants.h"
#include "flibrary.h"

#include "Chunk.h"
#include "Block.h"
#include "Blocklist.h"
#include "Spriteman.h"
//#include "Map.h"

using namespace sf;
using namespace std;

void drawLoop(RenderWindow * app, Chunk * map, Cspriteman *spriteman);
void drawDebug(RenderWindow * app, String verb);

int main()
{
    bool debug = false;
    
    int selectedBlock = 1;

    // Create the main window
    RenderWindow App(VideoMode(SCREEN_W, SCREEN_H), "E.O.W.",Style::Resize | Style::Close);

    Font pixelFont;

    if (!pixelFont.LoadFromFile(FNT_PATH "pixel.ttf", 16))
        return EXIT_FAILURE;
    
    String VerboseVariables("TEST", pixelFont, 16);
    VerboseVariables.SetColor(sf::Color(165, 0, 0));

    Event Event;

    // Gestion des images
    Cspriteman *spriteman;
    spriteman = Cspriteman::Initialize("blocks.png", "decals.png");
    //cout << "Singleton de management de sprites crée à l'adresse : " << spriteman << endl;

    // Gestion des blocks types
    Cblocklist blocklist;
    blocklist.addBlock("Empty Space", "Thin air.",false);
    blocklist.addBlock("Dirt", "A block made of accumulated dirt",false);
    blocklist.addBlock("Sand", "A heap of sand.",false);
    blocklist.addBlock("Stone", "A block made of accumulated cobblestone.",false);
    blocklist.addBlock("Hardstone", "Hardest stone on blockland",false);

    // vectors pour la definition de la camera
    Vector2f Center(App.GetWidth()/2, App.GetHeight()/2);
    Vector2f HalfSize(App.GetWidth()/2, App.GetHeight()/2);
    View View(Center, HalfSize);
    // Bouge la camera avant de demarer
    View.Move(((MAP_W)*BLOCK_W)/2-(App.GetWidth()/2),(MAP_H/2-25)*BLOCK_H);

    App.SetFramerateLimit(60);

    Chunk Map(0, blocklist);
    Map.sequence();
    Map.rockBottom(4);

    Image hudImg;
    hudImg.LoadFromFile("./res/gfx/hud.png");
    hudImg.SetSmooth(false);
    
    Sprite hudBlock;
    Sprite hudSpr;
    hudSpr.SetImage(hudImg);

    // Start the game loop
    while (App.IsOpened())
    {
        // Process events
        while (App.GetEvent(Event))
        {
            switch (Event.Type)
            {
                case Event::Closed:
                    // Fermeture de l'application en cas de fermeture
                    App.Close();
                    break;
                
                case Event::Resized:
                    // TODO: Redimmensionnement de l'application
                    // Clear screen
                    Center.y = App.GetWidth()/2;
                    Center.x = App.GetHeight()/2;
                    HalfSize.y = App.GetWidth()/2;
                    HalfSize.x = App.GetHeight()/2;
                    View.SetCenter(Center);
                    View.SetHalfSize(HalfSize);
                    View.Move(((MAP_W)*BLOCK_W)/2-(App.GetWidth()/2),(MAP_H/2-25)*BLOCK_H);
                    
                    App.SetView(sf::View(sf::FloatRect(0, 0, Event.Size.Width,Event.Size.Height)));
                    
                    cout << "The window was resized to X=" << Event.Size.Width << " Y=" << Event.Size.Height << "." << endl;
                    cout << "The width/height from the window get functions: " << App.GetWidth() << "/" << App.GetHeight() << endl;
                    
                    App.Clear(Color(176,224,230));
                    // Draw the chunk
                    drawLoop(&App, &Map, spriteman);
                    // Dessiner les élements du debbuging (f1)
                    if (debug) drawDebug(&App, VerboseVariables);
                    break;
                
                case Event::GainedFocus:
                    // Focus
                    cout << "Window gained focus" << endl;
                    break;
                
                case Event::LostFocus:
                    // Perte de focus
                    cout << "Window lost focus" << endl;
                    break;
                
                case Event::KeyPressed:
                    // Pression d'une touche
                    switch (Event.Key.Code)
                    {
                        case Key::Escape:
                            App.Close();
                            break;
                        case Key::F1:
                            debug = !debug;
                            break;
                    }
                    break;
                
                case Event::MouseButtonPressed:
                    // Pression d'un bouton de la souris
                    switch (Event.MouseButton.Button)
                    {
                        case Mouse::Left:
                        {
                            Vector2f MousePos = App.ConvertCoords(
                                                App.GetInput().GetMouseX(),
                                                App.GetInput().GetMouseY());
                            Map.affectBlockSpAt(MousePos.x,
                                                MousePos.y);
                            break;
                        }
                        
                        case Mouse::Right:
                        {
                            Vector2f MousePos = App.ConvertCoords(
                                                App.GetInput().GetMouseX(),
                                                App.GetInput().GetMouseY());
                            Map.changeBlockTypeAt(MousePos.x,
                                                MousePos.y, selectedBlock);
                            break;
                        }
                    }
                    break;
                
                case Event::MouseWheelMoved:
                    // La molette de la souris est bougée
//                    cout << "wheel move : " << Event.MouseWheel.Delta << endl;
                    switch (Event.MouseWheel.Delta)
                    {
                        case 1:
                            if (selectedBlock >= blocklist.getBlocklistSize()-1)
                                selectedBlock = 1;
                            else
                                selectedBlock++;
                            
                            cout << "Block selectionné : " << selectedBlock << "/" << blocklist.getBlocklistSize()-1 << endl;
                            
                            break;
                        
                        case -1:
                            if (selectedBlock <= 1)
                                selectedBlock = blocklist.getBlocklistSize()-1;
                            else
                                selectedBlock--;
                            
                            cout << "Block selectionné : " << selectedBlock << "/" << blocklist.getBlocklistSize()-1 << endl;
                            
                            break;
                    }
                    break;
            }
        }

        // evenements permetant de deplacer la camera
        float Offset = 150.f * App.GetFrameTime();
        if (App.GetInput().IsKeyDown(sf::Key::Up))
        {
            View.Move( 0.f, -Offset);
        }
        if (App.GetInput().IsKeyDown(sf::Key::Down))
        {
            if (View.GetRect().Bottom <= MAP_H*BLOCK_H)
            {
                View.Move( 0.f, Offset);
            }
        }
        if (App.GetInput().IsKeyDown(sf::Key::Left))
        {
            View.Move(-Offset, 0.f);
        }
        if (App.GetInput().IsKeyDown(sf::Key::Right))
        {
            View.Move( Offset, 0.f);
        }

        // defini la vue de l'application
        App.SetView(View);

        // Efface l'ecran
        App.Clear(Color(176,224,230));

        // Draw the chunk
        drawLoop(&App, &Map, spriteman);

        hudBlock = spriteman->GetSpr(selectedBlock);
        hudBlock.SetScale(3,3);
//        hudBlock.SetX(SCREEN_W-hudBlock.GetSize().x);
//        hudBlock.SetY(SCREEN_H-hudBlock.GetSize().y);
        hudSpr.SetX(View.GetRect().Right - 54);
        hudSpr.SetY(View.GetRect().Bottom - 54);

        hudBlock.SetX(View.GetRect().Right - BLOCK_W*3);
        hudBlock.SetY(View.GetRect().Bottom - BLOCK_H*3);

        App.Draw(hudSpr);
        App.Draw(hudBlock);

        // Dessiner les élements du debbuging (f1)
        if (debug) drawDebug(&App, VerboseVariables);

        // Update the window
        App.Display();
    }
    
    spriteman->kill();
    
    return EXIT_SUCCESS;
}

void drawLoop(RenderWindow * app, Chunk * map, Cspriteman *spriteman)
{
    int x, 
        y,
        map_w = map->getW(),
        map_h = map->getH();

    View view = app->GetView();

    Sprite  spritetemp,
            decaltemp;

    Cblock  *TempBlock;

    for (x = 0; x < map_w; x++)
    {
        for (y = 0; y < map_h; y++)
        {
        
        TempBlock = (map->GetBlock(x,y));
        int temptype = TempBlock->getType();
        
            if (temptype > 0 && TempBlock->getSp() > 0)
            {
                if ((view.GetRect()).Contains
                    (x*BLOCK_W - BLOCK_W, y*BLOCK_H + BLOCK_H)
                    || (view.GetRect()).Contains
                    (x*BLOCK_W + BLOCK_W, y*BLOCK_H - BLOCK_H)
                    || (view.GetRect()).Contains
                    (x*BLOCK_W + BLOCK_W, y*BLOCK_H + BLOCK_H)
                    || (view.GetRect()).Contains
                    (x*BLOCK_W - BLOCK_W, y*BLOCK_H - BLOCK_H))
                {
                    // On demande le sprite à afficher au manager de sprites
                    spritetemp = spriteman->GetSpr(temptype);
                    spritetemp.SetX(x*BLOCK_W);
                    spritetemp.SetY(y*BLOCK_H);
                    app->Draw(spritetemp);
                    if (temptype == 1)
                    {
                        if (TempBlock->isGrassy())
                        {
                            decaltemp = spriteman->GetDecal(0);
                            decaltemp.SetX(x*BLOCK_W);
                            decaltemp.SetY(y*BLOCK_H);
                            app->Draw(decaltemp);
                        }
                    }
                }
            }
        }
    }
}

void drawDebug(RenderWindow * app, String verb)
{
    View view = app->GetView();

    Vector2f MousePos = app->ConvertCoords(app->GetInput().GetMouseX(), app->GetInput().GetMouseY());

    verb.SetText(
    "Bottom = " + float2string(((view.GetRect()).Bottom) / 16.f) 
    + "    Top = " + float2string(((view.GetRect()).Top) / 16.f) 
    + "    Right = " + float2string(((view.GetRect()).Right) / 16.f)
    + "    Left = " + float2string(((view.GetRect()).Left) / 16.f)
    + "\n Absolute mouse coordinates : Mouse.x = " + float2string(MousePos.x)
    + "     Mouse.y = " + float2string(MousePos.y)
    + "\n Relative mouse coordinates : Mouse.x = " + float2string(app->GetInput().GetMouseX())
    + "     Mouse.y = " + float2string(app->GetInput().GetMouseY()));
    verb.SetPosition(((view.GetRect()).Left), ((view.GetRect()).Top));
    app->Draw(verb);
}
