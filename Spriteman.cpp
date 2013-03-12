#include "Spriteman.h"

namespace eow
{
    // Initialisation du singleton à NULL
    Cspriteman *Cspriteman::_singleton = NULL;

    // Constructeur
    Cspriteman::Cspriteman(string const& e_imgPath)
    {
        unsigned int x, y;
        // On charge l'image
        m_sprSheetImg.LoadFromFile(GFX_PATH + e_imgPath);

        // Le smoothing c'est mal !
        m_sprSheetImg.SetSmooth(false);
        
        // On crée des sprites à partir de l'image
        m_sprSheetSpr.SetImage(m_sprSheetImg);

        for (x = 0; x < 30; x++)
        {
            for(y = 0; y < 3; y++)
            {
                Sprite newSprite(m_sprSheetImg);
                Rect<int> test(x*BLOCK_W,(y+1)*BLOCK_H,(x+1)*BLOCK_W,y*BLOCK_H);
                newSprite.SetSubRect(test);
                newSprite.SetCenter(0,-BLOCK_H);
                
                // Selon la ligne à laquelle on est, on sait si il s'agit d'un block
                // ou d'un decal
                if (y == 0)
                {
                    // Il s'agit d'une image de block
                    m_subTile.push_back(newSprite);
                }
                else if (y >= 2)
                {
                    // Il s'agit d'un decal
                    m_subDecal.push_back(newSprite);
    //                m_decalColors.push_back(newSprite.GetPixel(8, 8));
                }
            }
        }
        
        int total = 0;
        DIR *dir;
        struct dirent *ent;
        
        char* path(GFX_GUI_PATH);
        
        dir = opendir(path);
        if (dir == NULL)
        {
            cout << "Impossible to open " << path << " directory." << endl;
        }
        else
        {
            // pour chaque ellement dans le dossier
            while ((ent = readdir(dir)) != NULL)
            {
                string  fileName(ent->d_name),
                        shortFileName,
                        ending(GFX_FILE_EXTENT);
                // Verifie si le fichier se termine par l'extention supportée
                // Si c'est le cas il est ajouté à la map
                if (fileName.length() >= ending.length())
                {
                    Image *tempImage = new Image();
                    tempImage->SetSmooth(false);
                    
                    int isCorrectExtent (0 == fileName.compare(
                            fileName.length() - ending.length(),
                            ending.length(), ending)),
                            error = 0;
                    if (!isCorrectExtent)
                    {
                        cout << "Wrong file type for " << fileName << 
                                " in the " << path << " directory. Ignored." << endl;
                        cout << "Supported extention is : " << GFX_FILE_EXTENT << " ." << endl;
//                        musicMap[shortFileName] = tempMusic;
                    }
                    
                    if (!tempImage->LoadFromFile(path + fileName))
                    {
                        cout << "Error while openning the image file " <<
                                fileName << " ." << endl;
                        error = true;
                    }
                    
                    if (!error)
                    {
                        Sprite tempSprite;
                        
                        m_guiImage.push_back(tempImage);
                        
                        tempSprite.SetImage(*m_guiImage.back());
                        
                        shortFileName = fileName.substr(
                                0, fileName.length() - ending.length());
                        m_guiElMap[shortFileName] = tempSprite;
                        total++;
                    }
                }
            }
            closedir(dir);
        }
        cout << total << " image(s) dinamically loaded successfully." << endl;
    }

    // Methodes
    // Getters
    Sprite Cspriteman::GetImageSpr(void)
    {
        return m_sprSheetSpr;
    }

    Sprite Cspriteman::GetTileSpr(unsigned int e_type)
    {
        return m_subTile[e_type];
    }

    Sprite Cspriteman::GetDecalSpr(unsigned int e_type)
    {
        return m_subDecal[e_type];
    }

    // toString
    string Cspriteman::toString(void)
    {
        ostringstream ret;
        if (NULL == _singleton)
        {
            ret << "Sprite manager not created." << endl;
        }
        else
        {
            ret << "Sprite manager created at " << _singleton  << "." << endl;
        }
        return ret.str();
    }

    Sprite Cspriteman::GetGuiSpr(string const& e_name)
    {
        return m_guiElMap[e_name];
    }

    // Methodes statiques
    Cspriteman* Cspriteman::Initialize(string const& e_imgPath)
    {
        if (_singleton == NULL)
        {
            _singleton =  new Cspriteman(e_imgPath);
        }
        return _singleton;
    }

    void Cspriteman::kill()
    {
        if (_singleton != NULL)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }
}; /* namespace eow */

