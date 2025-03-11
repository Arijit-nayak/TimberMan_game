#include<SFML/Graphics.hpp>
#include<cmath>
#include<unistd.h>
#include<sstream>
using namespace sf;

void updateCloudSprite(Sprite &sp, Time &dt, float &pixpsec){
    if(true){
        float x = sp.getPosition().x + dt.asSeconds() * pixpsec;
        float y = sp.getPosition().y;

        if(x>1920){
            sp.setPosition(-300, y);
        }
        else{
            sp.setPosition(x, y);
        }
    }
}
void updateBeeSprite(Sprite &sp, Time &dt, float &pixpsec){
    static int beeDir = 1;
    static float timex = 0.0f;
    timex += dt.asSeconds();
    float x = sp.getPosition().x - dt.asSeconds() * pixpsec;
    float y = 880 + beeDir * 50 * sin(timex* 1);

    if(sp.getPosition().y < 840 || sp.getPosition().y > 920){
        beeDir = beeDir * pow(-1, rand()%2);
        timex = 0.0f;
    }

    if(x < 0){
        sp.setPosition(1900, y);
        beeDir = 1;
    }
    else{
        sp.setPosition(x, y);
    }
}

int main(){
    VideoMode vm(800, 600);
    RenderWindow window(vm, "Timber Man");

    View view(FloatRect(0,0,1920,1080));
    window.setView(view);


    Sprite spriteBackground;
    Texture textureBackground;
    textureBackground.loadFromFile("background.png");
    spriteBackground.setTexture(textureBackground);

    Sprite spriteCloud;
    Texture textureCloud;
    textureCloud.loadFromFile("cloud.png");
    spriteCloud.setTexture(textureCloud);
    spriteCloud.setPosition(0, 30);
    spriteCloud.setScale(0.5, 0.5);
    bool moveCloud = false;
    float cloudSpeed = 35;
    float pixelPerSecondCloud = 1920/cloudSpeed;

    Sprite spriteCloud1;
    textureCloud.loadFromFile("cloud.png");
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 80);
    float cloudSpeed1 = 25;
    float pixelPerSecondCloud1 = 1920/cloudSpeed1;

    Sprite spriteCloud2;
    textureCloud.loadFromFile("cloud.png");
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setPosition(0, 150);
    spriteCloud2.setScale(0.8, 0.8);
    float cloudSpeed2 = 30;
    float pixelPerSecondCloud2 = 1920/cloudSpeed2;

    Sprite spriteBee;
    Texture textureBee;
    textureBee.loadFromFile("bee.png");
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(1920,900);
    bool moveBee = false;
    float beeSpeed = 20;
    float pixelPerSecondBee = 1920/beeSpeed;

    Sprite spriteTree;
    Texture textureTree;
    textureTree.loadFromFile("tree.png");
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    int score_val = 0;
    String score = "Score = 0";

    Text scoreMessage;
    Font font;
    font.loadFromFile("KOMIKAP_.ttf");
    scoreMessage.setFont(font);
    scoreMessage.setFillColor(Color :: Yellow);
    scoreMessage.setString("Score = 0");
    scoreMessage.setCharacterSize(80);
    scoreMessage.setPosition(100, 10);

    FloatRect scoreRect;
    bool acceptInput = true;
    bool gamestart = false;

    Clock ct;
    Time dt;

    while(window.isOpen()){

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            if(event.type == Event::KeyReleased && acceptInput == false){
                acceptInput = true;
            }
        }

        dt = ct.restart();
        if(moveCloud){
            updateCloudSprite(spriteCloud, dt, pixelPerSecondCloud);
            updateCloudSprite(spriteCloud1, dt, pixelPerSecondCloud1);
            updateCloudSprite(spriteCloud2, dt, pixelPerSecondCloud2);
        }

        if(moveBee){
            updateBeeSprite(spriteBee, dt, pixelPerSecondBee);
        }

        if(Keyboard::isKeyPressed(Keyboard::Return)){
            moveCloud = true;
            moveBee = true;
            gamestart = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        if(acceptInput && gamestart){
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                score_val ++;
                acceptInput = false;
            }

            if(Keyboard::isKeyPressed(Keyboard::Right)){
                score_val ++;
                acceptInput = false;
            }   
        }
        

        std::stringstream ss;
        ss << "Score: " << score_val;
        scoreMessage.setString(ss.str());

        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);

        window.draw(spriteTree);

        window.draw(spriteBee);

        window.draw(scoreMessage);
        window.display();
    }
    return(0); 
}