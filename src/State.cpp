#include "State.h"
#include "Game.h"
#include <iostream>
#include "Zombie.h"
#include "SDL_include.h"  
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Character.h"
#include "PlayerController.h"

#include <iostream>
#include <algorithm> 

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

State::State() : quitRequested(false), started(false) {
}

State::~State() {
    objectArray.clear(); 
}

void State::Start() {
    if (started) return;
    LoadAssets();
    for(const auto& objPtr : objectArray) {
        if(objPtr) {
            objPtr->Start();
        }
    }
    started = true;
}

void State::LoadAssets() {
    std::cout << "State::LoadAssets: Carregando assets..." << std::endl;

    // --- Fundo ---
    GameObject* bgGO = new GameObject();
    bgGO->box.x = 0;
    bgGO->box.y = 0;
    // Certifique-se que o caminho "recursos/img/Background.png" está correto e a imagem existe.
    SpriteRenderer* bgSprite = new SpriteRenderer(*bgGO, "recursos/img/Background.png");
    bgSprite->SetCameraFollower(true); // Fundo deve permanecer fixo na tela
    bgGO->AddComponent(bgSprite);

    // Garante que o fundo preencha a tela (exemplo: janela 1200x900)
    // Se a imagem já for do tamanho da janela, não precisa escalar.
    // Caso contrário, faz o ajuste de escala.
    if (bgSprite->GetSprite() && bgSprite->GetSprite()->IsOpen()) {
        float currentBgWidth = bgGO->box.w;  // Largura definida pelo SpriteRenderer
        float currentBgHeight = bgGO->box.h; // Altura definida pelo SpriteRenderer
        float targetWidth = static_cast<float>(Game::GetInstance().GetWindowWidth());
        float targetHeight = static_cast<float>(Game::GetInstance().GetWindowHeight());

        if (currentBgWidth > 0 && currentBgHeight > 0) { // Evita divisão por zero
            float scaleX = targetWidth / currentBgWidth;
            float scaleY = targetHeight / currentBgHeight;
            bgSprite->SetScale(scaleX, scaleY); // Atualiza o tamanho do GameObject
            std::cout << "State::LoadAssets: Fundo escalado para X: " << scaleX << ", Y: " << scaleY << std::endl;
        } else {
            std::cerr << "State::LoadAssets: Sprite do fundo carregado com dimensões zero, não é possível escalar." << std::endl;
            bgGO->box.w = targetWidth; // Ajuste forçado
            bgGO->box.h = targetHeight;
        }
    } else {
        std::cerr << "State::LoadAssets: Falha ao carregar sprite do fundo, forçando tamanho do GameObject." << std::endl;
        bgGO->box.w = static_cast<float>(Game::GetInstance().GetWindowWidth());
        bgGO->box.h = static_cast<float>(Game::GetInstance().GetWindowHeight());
    }
    AddObject(bgGO);
    std::cout << "State::LoadAssets: Fundo carregado." << std::endl;

    // --- TileMap ---
    // Certifique-se que os caminhos estão corretos.
    GameObject* mapGO = new GameObject();
    mapGO->box.x = 0;
    mapGO->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "recursos/img/Tileset.png");
    TileMap* tileMap = new TileMap(*mapGO, "recursos/map/map.txt", tileSet);
    mapGO->AddComponent(tileMap);
    AddObject(mapGO);
    std::cout << "State::LoadAssets: TileMap carregado." << std::endl;

    // --- Música ---
    // Certifique-se que o caminho está correto.
    music.Open("recursos/audio/BGM.wav");
    if(!music.IsOpen()) {
        std::cerr << "State::LoadAssets Erro: Falha ao carregar música de fundo!" << std::endl;
    } else {
        music.Play(-1); // Loop infinito
        Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // Volume em 25%
        std::cout << "State::LoadAssets: Música carregada e tocando." << std::endl;
    }

    // --- Personagem do Jogador ---
    // Certifique-se que o caminho e as configurações do sprite estão corretos.
    GameObject* charGO = new GameObject();
    charGO->box.x = 1280; // Posição inicial no mundo
    charGO->box.y = 1280; // Posição inicial no mundo

    // O construtor de Character configura o SpriteRenderer e Animator.
    Character* charComponent = new Character(*charGO, "recursos/img/Player.png");
    charGO->AddComponent(charComponent);

    PlayerController* pController = new PlayerController(*charGO);
    charGO->AddComponent(pController);

    std::weak_ptr<GameObject> charWeakPtr = AddObject(charGO);
    std::cout << "State::LoadAssets: Personagem e PlayerController criados." << std::endl;

    // Define referência estática do player para acesso global, se necessário
    if (Character::player == nullptr) {
        Character::player = charComponent;
        std::cout << "State::LoadAssets: Referência estática Character::player definida." << std::endl;
    }

    // Configura a câmera para seguir o jogador
    if (!charWeakPtr.expired()) {
        Camera::GetInstance().Follow(charWeakPtr.lock().get());
        std::cout << "State::LoadAssets: Câmera agora segue o jogador." << std::endl;
    } else {
        std::cerr << "State::LoadAssets Aviso: Não foi possível recuperar o GameObject do personagem para a câmera. Usando ponteiro bruto." << std::endl;
        Camera::GetInstance().Follow(charGO);
    }
    std::cout << "State::LoadAssets: Finalizado." << std::endl;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    if (go == nullptr) {
        return std::weak_ptr<GameObject>();
    }
    std::shared_ptr<GameObject> sharedGo(go);
    objectArray.push_back(sharedGo);

    if(started) {
        go->Start();
    }
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    if (go == nullptr) {
        return std::weak_ptr<GameObject>();
    }
    for (const auto& objPtr : objectArray) {
        if (objPtr.get() == go) {
            return std::weak_ptr<GameObject>(objPtr);
        }
    }
    return std::weak_ptr<GameObject>();
}

void State::Update(float dt) {
     // Verifica se o usuário pediu para sair do jogo
     InputManager& input = InputManager::GetInstance();
     if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
         quitRequested = true;
     }

    // Spawn de zumbis ao pressionar espaço
    if(input.KeyPress(SPACE_KEY)) {
        Vec2 mousePos(static_cast<float>(input.GetMouseX()), static_cast<float>(input.GetMouseY()));
        Vec2 cameraPos = Camera::GetInstance().GetPos();
        Vec2 worldMousePos = mousePos + cameraPos;

        GameObject* zombieGO = new GameObject();
        zombieGO->box.x = worldMousePos.x - zombieGO->box.w / 2; // Centraliza no mouse
        zombieGO->box.y = worldMousePos.y - zombieGO->box.h / 2;
        zombieGO->AddComponent(new Zombie(*zombieGO));
        AddObject(zombieGO);
    }

    // Atualiza a câmera
    Camera::GetInstance().Update(dt);

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
    
    // Atualiza todos os objetos
    for(auto& obj : objectArray) {
        obj->Update(dt);
    }
    
    for(size_t i = 0; i < objectArray.size(); ++i) {
        if(objectArray[i]) {
            objectArray[i]->Update(dt);
        }
    }
    
    // Remove objetos mortos de forma eficiente
    objectArray.erase(std::remove_if(objectArray.begin(), objectArray.end(),
        [](const std::shared_ptr<GameObject>& objPtr) {
            return objPtr->IsDead();
        }), objectArray.end());
}

void State::Render() {
    for(const auto& objPtr : objectArray) {
        if(objPtr) {
            objPtr->Render();
        }
    }
}

bool State::QuitRequested() {
    return quitRequested;
}
