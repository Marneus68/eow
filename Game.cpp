#include "Game.h"

namespace eow
{
    // Initialisation du singleton
    Game *Game::_singleton = NULL;
    
    void Game::pre_init(void)
    {
        // Create the main window
        renderWindow.Create(VideoMode(SCREEN_W, SCREEN_H),
                m_title,Style::Resize | Style::Close);
        
        renderWindow.UseVerticalSync(true);
    }
    
    void Game::init(void)
    {
        inventory = false;
        
        showmmap = 1;
        
        if (!pixelFont.LoadFromFile(FNT_PATH "pixel.ttf", 16))
            cout << "Failed to load the font" << endl;
        
        cout << "Attempting to start the sprite manager." << endl;
        spriteman = eow::Cspriteman::Initialize("blocks.png");
        cout << "Sprite manager initialised." << endl;
        
        musicman = eow::Csoundman::Initialize();
        
        blocklist.addBlock(false, Color(176, 224, 230));
        blocklist.addBlock(false, Color(61, 42, 27));
        blocklist.addBlock(false, Color(228, 203, 136));
        blocklist.addBlock(false, Color(111,111,111));
        blocklist.addBlock(false, Color(147, 147, 147));
        
        map = new eow::Chunk(0, &blocklist);
        map->sequence();
        map->rockBottom(4);
    }
    
    void Game::main_loop(void)
    {
        // TODO : Quelques declarations sales à netoyer
        
        eow::Cminimap mmap(map);
        
        Vector2f Center(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2);
        Vector2f HalfSize(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2);
        View view(Center, HalfSize);
        // Bouge la camera avant de demarer
        // TODO : on ne devrai pas utilsier .Move, mais quelquechose comme 
        // .SetFromRect(FloatRect())
        view.Move(((MAP_W)*BLOCK_W)/2-(renderWindow.GetWidth()/2),
                (MAP_H/2-25)*BLOCK_H);
        
        bool    debug = false;
        int     selectedBlock = 1;
        
        Sprite hudBlock;
        
        Sprite mmapSpr;
        
        Sprite skyBoxSpr;
        Image skyBoxImg;
        skyBoxImg.SetSmooth(false);
        string skyBoxPath("sky.png");
        skyBoxImg.LoadFromFile(GFX_PATH + skyBoxPath);
        skyBoxSpr.SetImage(skyBoxImg);
        
        Sprite hudSpr = spriteman->GetGuiSpr("hud");
        
        Sprite mmapHudRightSpr = spriteman->GetGuiSpr("maphud_right");
        
        Sprite mmapHudTopSpr = spriteman->GetGuiSpr("maphud_top");
        
        Sprite mmapHudCornerOpenSpr = spriteman->GetGuiSpr("maphud_corner_open");
        
        Sprite mmapHudCornerClosedSpr = spriteman->GetGuiSpr("maphud_corner_closed");
        
        Sprite hudInvEndClosedSpr = spriteman->GetGuiSpr("inventory_end_closed");
        
        Sprite hudInvEndOpenSpr = spriteman->GetGuiSpr("inventory_end_open");
        
        Sprite hudInvSlotSpr = spriteman->GetGuiSpr("inventory_slot");
        
        Sprite hudInvSelectorSpr = spriteman->GetGuiSpr("inventory_slot_selector");

        // Start the game loop
        while (renderWindow.IsOpened())
        {
            // Process events
            while (renderWindow.GetEvent(Event))
            {
                switch (Event.Type)
                {
                    case Event::Closed:
                        // Fermeture de l'application en cas de fermeture
                        renderWindow.Close();
                        break;
                        
                        // Focus
                    case Event::GainedFocus:
                            cout << "Window gained focus" << endl;
                        break;
                    
                    case Event::LostFocus:
                        // Perte de focus
                        if (debug)
                            cout << "Window lost focus" << endl;
                        break;
                    
                    case Event::KeyPressed:
                        // Pression d'une touche
                        switch (Event.Key.Code)
                        {
                            case Key::Escape:
                                renderWindow.Close();
                                break;
                            case Key::I:
                                inventory = !inventory;
                                break;
                            case Key::P:
                            {
                                if (showmmap > 1)
                                    showmmap = 0;
                                else if (showmmap >= 0)
                                    showmmap++;
                                
                                break;
                            }
                            case Key::F1:
                                debug = !debug;
                                break;
                            case Key::F12:
                                screenCap = renderWindow.Capture();
                                screenCap.SaveToFile("screenshot.png");
                                break;
                        }
                        break;
                    
                    case Event::MouseButtonPressed:
                        // Pression d'un bouton de la souris
                        switch (Event.MouseButton.Button)
                        {
                            case Mouse::Left:
                            {
                                Vector2f MousePos = renderWindow.ConvertCoords(
                                                    renderWindow.GetInput().GetMouseX(),
                                                    renderWindow.GetInput().GetMouseY());
                                map->affectBlockSpAt(MousePos.x,
                                                    MousePos.y);
                                break;
                            }
                            
                            case Mouse::Right:
                            {
                                Vector2f MousePos = renderWindow.ConvertCoords(
                                                    renderWindow.GetInput().GetMouseX(),
                                                    renderWindow.GetInput().GetMouseY());
                                map->changeBlockTypeAt(MousePos.x,
                                                    MousePos.y, selectedBlock);
                                
                                //musicman->playSound("click");
                                
                                break;
                            }
                        }
                        break;
                    
                    case Event::MouseWheelMoved:
                        // La molette de la souris est bougée
                        // cout << "wheel move : " << Event.MouseWheel.Delta << endl;
                        switch (Event.MouseWheel.Delta)
                        {
                            case -1:
                                if (selectedBlock >= blocklist.getBlocklistSize()-1)
                                    selectedBlock = 1;
                                else
                                    selectedBlock++;
                                
                                if (debug)
                                    cout << "Selected block : " << 
                                            selectedBlock << "/" << 
                                            blocklist.getBlocklistSize()-1 << endl;
                                
                                break;
                            
                            case 1:
                                if (selectedBlock <= 1)
                                    selectedBlock = blocklist.getBlocklistSize()-1;
                                else
                                    selectedBlock--;
                                    
                                if (debug)
                                    cout << "Selected block : " << 
                                            selectedBlock << "/" << 
                                            blocklist.getBlocklistSize()-1 << endl;
                                
                                break;
                        }
                        break;
                }
            }

            // evenements permetant de deplacer la camera
            
            //si la touche shift est pressée, elle augmente la vitess de deplacement
            float Offset;
            if (renderWindow.GetInput().IsKeyDown(sf::Key::LShift))
            {
                Offset = 300.f * renderWindow.GetFrameTime();
            }
            else
            {
                Offset = 150.f * renderWindow.GetFrameTime();
            }
            
            // deplacement vers le haut
            if (renderWindow.GetInput().IsKeyDown(sf::Key::Up))
            {
                view.Move( 0.f, -Offset);
            }
            
            // deplacement vers le bas
            if (renderWindow.GetInput().IsKeyDown(sf::Key::Down))
            {
                if (view.GetRect().Bottom <= MAP_H*BLOCK_H)
                {
                    view.Move( 0.f, Offset);
                }
            }
            
            // deplacement vers la gauche
            if (renderWindow.GetInput().IsKeyDown(sf::Key::Left))
            {
                if (view.GetRect().Left <= 0)
                    view.SetFromRect(FloatRect(
                            map->getW()*BLOCK_W,
                            view.GetRect().Top,
                            map->getW()*BLOCK_W + renderWindow.GetWidth(),
                            view.GetRect().Bottom));
                else
                    view.Move(-Offset, 0.f);
            }
            
            // deplacement vers la droite
            if (renderWindow.GetInput().IsKeyDown(sf::Key::Right))
            {
                if (view.GetRect().Left >= map->getW()*BLOCK_W)
                    view.SetFromRect(FloatRect(
                            view.GetRect().Left - (map->getW()*BLOCK_W),
                            view.GetRect().Top,
                            view.GetRect().Left - (map->getW()*BLOCK_W) + view.GetRect().GetWidth(),
                            view.GetRect().Bottom));
                else
                    view.Move( Offset, 0.f);
            }

            // defini la vue de la fenêtre de l'application
            renderWindow.SetView(view);

            // Efface l'ecran
            renderWindow.Clear(Color(176,224,230));

            // Dessin du ciel paralaxé
            for(int i = 0; i < (view.GetHalfSize().x * 2) / skyBoxSpr.GetSize().x + 1; i++)
            {
                bgdecal = i + view.GetRect().Left / skyBoxSpr.GetSize().x;
                
                skyBoxSpr.SetX((view.GetRect().Left) + (skyBoxSpr.GetSize().x * bgdecal) - view.GetRect().Left);
                skyBoxSpr.SetY(view.GetCenter().y - skyBoxSpr.GetSize().y/2);
                
                renderWindow.Draw(skyBoxSpr);
            }

            // Draw the chunk
            drawLoop(map);

            // dessin conditionnel de la partie inventaire du hud
            if (inventory)
            {
                hudInvEndOpenSpr.SetX(view.GetRect().Right - hudInvEndOpenSpr.GetSize().x - hudSpr.GetSize().x - (hudInvSlotSpr.GetSize().x * (blocklist.getBlocklistSize() - 1)));
                hudInvEndOpenSpr.SetY(view.GetRect().Bottom - hudInvEndOpenSpr.GetSize().y);
                renderWindow.Draw(hudInvEndOpenSpr);
                
                int i;
                for (i = 0; i < blocklist.getBlocklistSize() - 1; i++)
                {
                    Sprite tempsprite;
                    
                    hudInvSlotSpr.SetX(hudInvEndOpenSpr.GetPosition().x + hudInvEndOpenSpr.GetSize().x + (hudInvSlotSpr.GetSize().x * i));
                    hudInvSlotSpr.SetY(hudInvEndOpenSpr.GetPosition().y);
                    renderWindow.Draw(hudInvSlotSpr);
                    
                    tempsprite = spriteman->GetTileSpr(i+1);
                    tempsprite.SetX(hudInvSlotSpr.GetPosition().x + 3);
                    tempsprite.SetY(hudInvEndOpenSpr.GetPosition().y + 8);
                    renderWindow.Draw(tempsprite);
                    
                    if (i+1 == selectedBlock)
                    {
                        hudInvSelectorSpr.SetPosition(hudInvSlotSpr.GetPosition());
                        renderWindow.Draw(hudInvSelectorSpr);
                    }
                }
            }
            else
            {
                // l'inventaire est fermé
                hudInvEndClosedSpr.SetX(view.GetRect().Right - hudInvEndClosedSpr.GetSize().x - hudSpr.GetSize().x);
                hudInvEndClosedSpr.SetY(view.GetRect().Bottom - hudInvEndClosedSpr.GetSize().y);
                renderWindow.Draw(hudInvEndClosedSpr);
            }
            
            // dessin de la partie block du hud
            hudBlock = spriteman->GetTileSpr(selectedBlock);
            hudBlock.SetScale(3,3);
            hudSpr.SetX(view.GetRect().Right - hudSpr.GetSize().x); //54
            hudSpr.SetY(view.GetRect().Bottom - hudSpr.GetSize().y); //54

            hudBlock.SetX(view.GetRect().Right - BLOCK_W*3);
            hudBlock.SetY(view.GetRect().Bottom - BLOCK_H*3);

            renderWindow.Draw(hudSpr);
            renderWindow.Draw(hudBlock);

            // dessine la minimap
            if (showmmap > 0)
            {
                mmap.redrawMmap();
                mmapSpr = mmap.getMmapSpr();
                if (showmmap == 2)
                    mmapSpr.SetScale(0.5, 0.5);
                mmapSpr.SetX(view.GetRect().Left);
                mmapSpr.SetY(view.GetRect().Bottom - mmapSpr.GetSize().y);
                
                mmapHudCornerOpenSpr.SetX(view.GetRect().Left + mmapSpr.GetSize().x);
                mmapHudCornerOpenSpr.SetY(view.GetRect().Bottom - mmapHudCornerOpenSpr.GetSize().y - mmapSpr.GetSize().y);
                
                for (int i = 0; i <= mmapSpr.GetSize().y; i++)
                {
                    mmapHudRightSpr.SetX(view.GetRect().Left + mmapSpr.GetSize().x);
                    mmapHudRightSpr.SetY(view.GetRect().Bottom - i);
                    
                    renderWindow.Draw(mmapHudRightSpr);
                }
                
                for (int i = 0; i <= mmapSpr.GetSize().y; i++)
                {
                    mmapHudTopSpr.SetX(view.GetRect().Left + i);
                    mmapHudTopSpr.SetY(view.GetRect().Bottom - mmapSpr.GetSize().y - mmapHudTopSpr.GetSize().y);
                    
                    renderWindow.Draw(mmapHudTopSpr);
                }
                
                renderWindow.Draw(mmapSpr);
                renderWindow.Draw(mmapHudCornerOpenSpr);
            }
            else
            {
                mmapHudCornerClosedSpr.SetX(view.GetRect().Left);
                mmapHudCornerClosedSpr.SetY(view.GetRect().Bottom - mmapHudCornerClosedSpr.GetSize().y);
                
                renderWindow.Draw(mmapHudCornerClosedSpr);
            }

            // Dessiner les élements du debbuging (f1)
            if (debug) drawDebug();

            // Update the window
            renderWindow.Display();
        }
    }
    
    void Game::cleanup(void)
    {
        spriteman->kill();
        musicman->kill();
    }
    
    void Game::drawLoop(eow::Chunk * map)
    {
        float   x,
                y;
        int map_w = map->getW(),
            map_h = map->getH();

        View view = renderWindow.GetView();

        Sprite  spritetemp,
                decaltemp;

        eow::Cblock *TempBlock;

        for (x = 0; x < map_w; x++)
        {
            for (y = 0; y < map_h; y++)
            {
                
                TempBlock = (map->GetBlock(x,y));
                int temptype = TempBlock->getType();
                int tempDecalType = TempBlock->getDecalType();
                
                if (temptype > 0 && TempBlock->getSp() > 0)
                {
                    if (view.GetRect().Contains
                        (x*BLOCK_W - BLOCK_W, y*BLOCK_H + BLOCK_H)
                        || (view.GetRect()).Contains
                        (x*BLOCK_W + BLOCK_W, y*BLOCK_H - BLOCK_H)
                        || (view.GetRect()).Contains
                        (x*BLOCK_W + BLOCK_W, y*BLOCK_H + BLOCK_H)
                        || (view.GetRect()).Contains
                        (x*BLOCK_W - BLOCK_W, y*BLOCK_H - BLOCK_H))
                    {
                        // On demande le sprite à afficher au manager de sprites
                        spritetemp = spriteman->GetTileSpr(temptype);
                        spritetemp.SetX(x*BLOCK_W);
                        spritetemp.SetY(y*BLOCK_H);
                        renderWindow.Draw(spritetemp);
                        
                        if (tempDecalType)
                        {
                            decaltemp = spriteman->GetDecalSpr(tempDecalType-1);
                            decaltemp.SetX(x*BLOCK_W);
                            decaltemp.SetY(y*BLOCK_H);
                            renderWindow.Draw(decaltemp);
                        }
                    }
                }
            }
        }
        if (view.GetRect().Right > map->getW()*BLOCK_W)
        {
            for (x = 0; x < map_w  - renderWindow.GetWidth() / BLOCK_W; x++)
            {
                for (y = 0; y < map_h; y++)
                {
                    TempBlock = (map->GetBlock(x,y));
                    int temptype = TempBlock->getType();
                    int tempDecalType = TempBlock->getDecalType();
                    
                    if (temptype > 0 && TempBlock->getSp() > 0)
                    {
                        // TODO : !!!
                        if (view.GetRect().Contains
                            (MAP_W*BLOCK_W + (x*BLOCK_W - BLOCK_W), y*BLOCK_H + BLOCK_H) || 
                            (view.GetRect()).Contains
                            (MAP_W*BLOCK_W + (x*BLOCK_W + BLOCK_W), y*BLOCK_H - BLOCK_H) || 
                            (view.GetRect()).Contains
                            (MAP_W*BLOCK_W + (x*BLOCK_W + BLOCK_W), y*BLOCK_H + BLOCK_H) || 
                            (view.GetRect()).Contains
                            (MAP_W*BLOCK_W + (x*BLOCK_W - BLOCK_W), y*BLOCK_H - BLOCK_H))
                        {
                            // On demande le sprite à afficher au manager de sprites
                            spritetemp = spriteman->GetTileSpr(temptype);
                            spritetemp.SetX(x*BLOCK_W + MAP_W*BLOCK_W);
                            spritetemp.SetY(y*BLOCK_H);
                            renderWindow.Draw(spritetemp);
                            
                            if (tempDecalType)
                            {
                                decaltemp = spriteman->GetDecalSpr(tempDecalType-1);
                                decaltemp.SetX(x*BLOCK_W + MAP_W*BLOCK_W);
                                decaltemp.SetY(y*BLOCK_H);
                                renderWindow.Draw(decaltemp);
                            }
                        }
                    }
                }
            }
        }
    }

    void Game::drawDebug()
    {
        String verb("TEST", pixelFont, 16);
        verb.SetColor(sf::Color(165, 0, 0));

        View view = renderWindow.GetView();

        Vector2f MousePos = renderWindow.ConvertCoords(renderWindow.GetInput().GetMouseX(), renderWindow.GetInput().GetMouseY());

        verb.SetText(
        "View coordinates : Bottom = " + float2string(((view.GetRect()).Bottom) / 16.f) 
        + "    Top = " + float2string(((view.GetRect()).Top) / 16.f) 
        + "    Right = " + float2string(((view.GetRect()).Right) / 16.f)
        + "    Left = " + float2string(((view.GetRect()).Left) / 16.f)
        + "\n Absolute mouse coordinates : Mouse.x = " + float2string(MousePos.x)
        + "     Mouse.y = " + float2string(MousePos.y)
        + "\n Relative mouse coordinates : Mouse.x = " + float2string(renderWindow.GetInput().GetMouseX())
        + "     Mouse.y = " + float2string(renderWindow.GetInput().GetMouseY())
        + "     Inventory = " + bool2string(inventory)
        + "\n Minimap = " + int2string(showmmap)
        + "     Background tiles offset= " + int2string(bgdecal));
        verb.SetPosition(((view.GetRect()).Left), ((view.GetRect()).Top));
        renderWindow.Draw(verb);
    }
    
    Game::Game(string const& e_title) : 
        m_title(e_title)
    {
        
    }
    
    // Public
    Game* Game::Initialize(string const& e_title)
    {
        if (_singleton == NULL)
        {
            _singleton =  new Game(e_title);
        }
        else
        {
            // Rien à faire
        }
        return _singleton;
    }
    
    void Game::kill(void)
    {
        if (_singleton != NULL)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }
    
    void Game::Run(void)
    {
        pre_init();
        init();
        main_loop();
        cleanup();
        
        return;
    }
}; /* namespace eow */

