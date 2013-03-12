#include "Soundman.h"

namespace eow
{
    // Initialisation du singleton à NULL
    Csoundman *Csoundman::_singleton = NULL;

    Csoundman::Csoundman()
    {
        int total = 0;
        DIR *dir;
        struct dirent *ent;
        
        char* path(MUS_PATH);
        
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
                        ending(MUS_FILE_EXTENT);
                // Verifie si le fichier se termine par l'extention supportée
                // Si c'est le cas il est ajouté à la map
                if (fileName.length() >= ending.length())
                {
                    Music *tempMusic = new sf::Music();
                    int isCorrectExtent (0 == fileName.compare(
                            fileName.length() - ending.length(),
                            ending.length(), ending)),
                            error = 0;
                    if (!isCorrectExtent)
                    {
                        cout << "Wrong file type for " << fileName << 
                                " in the " << path << " directory. Ignored." << endl;
                        cout << "Supported extention is : " << MUS_FILE_EXTENT << " ." << endl;
//                        musicMap[shortFileName] = tempMusic;
                    }
                    
                    if (!tempMusic->OpenFromFile(path + fileName))
                    {
                        cout << "Error while openning the music file " <<
                                fileName << " ." << endl;
                        error = true;
                    }
                    
                    if (!error)
                    {
                        shortFileName = fileName.substr(
                                0, fileName.length() - ending.length());
                        musicMap[shortFileName] = tempMusic;
                        total++;
                    }
                }
            }
            closedir(dir);
        }
        cout << total << " music(s) loaded successfully." << endl;
        
        total = 0;
        
        path = SND_PATH;
        
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
                        ending(MUS_FILE_EXTENT);
                // Verifie si le fichier se termine par l'extention supportée
                // Si c'est le cas il est ajouté à la map
                if (fileName.length() >= ending.length())
                {
                    Sound *tempSound = new Sound();
                    
                    SoundBuffer *tempSoundBuffer = new SoundBuffer();
                    
                    int isCorrectExtent (0 == fileName.compare(
                            fileName.length() - ending.length(),
                            ending.length(), ending)),
                            error = 0;
                    if (!isCorrectExtent)
                    {
                        cout << "Wrong file type for " << fileName << 
                                " in the " << path << " directory. Ignored." << endl;
                        cout << "Supported extention is : " << MUS_FILE_EXTENT << " ." << endl;
//                        musicMap[shortFileName] = tempMusic;
                    }
                    
                    if (!tempSoundBuffer->LoadFromFile(path + fileName))
                    {
                        cout << "Error while openning the music file " <<
                                fileName << " ." << endl;
                        error = true;
                    }
                    
                    if (!error)
                    {
                        tempSound->SetBuffer(*tempSoundBuffer);
                        
                        shortFileName = fileName.substr(
                                0, fileName.length() - ending.length());
                        soundMap[shortFileName] = tempSound;
                        total++;
                    }
                }
            }
            closedir(dir);
        }
        cout << total << " sound(s) loaded successfully." << endl;
        
        
        
    }

    Csoundman::~Csoundman()
    {
        map<string, pointMusic>::iterator p;
        for(p = musicMap.begin(); p != musicMap.end(); p++) {
            p->second->~Music();
            delete p->second;
        }
        
        map<string, pointSound>::iterator t;
        for(t = soundMap.begin(); t != soundMap.end(); t++) {
            t->second->~Sound();
            delete t->second;
        }
    }

    // Methodes musiques
    void Csoundman::playMusic(string const& e_musName)
    {
        Music *localMus;
        localMus = musicMap[e_musName];
//        if (!localMus = musicMap[e_musName])
//            return;
        if (localMus->GetStatus() != sf::Music::Playing)
        {
            localMus->Play();
            cout << "Starting music " << e_musName << MUS_FILE_EXTENT << " ." << endl;
        }
    }

    void Csoundman::stopMusic(string const& e_musName)
    {
        Music *localMus;
        localMus = musicMap[e_musName];
//        if (!localMus = musicMap[e_musName])
//            return;
        if (localMus->GetStatus() == sf::Music::Playing)
        {
            localMus->Stop();
            cout << "Stoping music " << e_musName << MUS_FILE_EXTENT << " ." << endl;
        }
    }

    void Csoundman::setLoopMusic(string const& e_musName, bool e_loop)
    {
        Music *localMus;
        localMus = musicMap[e_musName];
//        if (!localMus = musicMap[e_musName])
//            return;
        localMus->SetLoop(e_loop);
    }

    // Musiques sons
    void Csoundman::playSound(string const& e_sndName)
    {
        Sound *localSound;
        localSound = soundMap[e_sndName];
        localSound->Play();
    }
    
    void Csoundman::stopSound(string const& e_sndName)
    {
        Sound *localSound;
        localSound = soundMap[e_sndName];
        localSound->Stop();
    }
    
    void Csoundman::setLoopSound(string const& e_sndName, bool e_loop)
    {
        Sound *localSound;
        localSound = soundMap[e_sndName];
        localSound->SetLoop(e_loop);
    }

    // Methodes statiques
    Csoundman* Csoundman::Initialize()
    {
        if (_singleton == NULL)
        {
            _singleton =  new Csoundman();
        }
        else
        return _singleton;
    }

    void Csoundman::kill()
    {
        if (_singleton != NULL)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }
}; /* namespace eow */

