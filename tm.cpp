#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cmath>
#include <sstream>
using namespace sf;

void updateCloudSprite(Sprite &spriteCloud, Time &dt, float &pixelPerSecondCloud)
{
    float x = spriteCloud.getPosition().x + dt.asSeconds() * pixelPerSecondCloud;
    float y = spriteCloud.getPosition().y;
    if (x > 1920)
    {
        spriteCloud.setPosition(-300, y);
    }
    else
    {
        spriteCloud.setPosition(x, y);
    }
}
void updateBeeSprite(Sprite &spriteBee, Time &dt, float &pixelPerSecondBee)
{
    //(rand()%50) -25
    static int beeDirection = 1;
    static float timex = 0.0f;
    timex += dt.asSeconds();
    float x = spriteBee.getPosition().x - dt.asSeconds() * pixelPerSecondBee;
    float y = 880 + beeDirection * 50 * sin(timex * 1);
    if (spriteBee.getPosition().y < 840 || spriteBee.getPosition().y > 920)
    {
        beeDirection = beeDirection * pow(-1, rand() % 2);
        timex = 0.0f;
    }
    if (x < 0)
    {
        spriteBee.setPosition(2100, 880);
        beeDirection = 1;
    }
    else
    {
        spriteBee.setPosition(x, y);
    }
}
void upadteTimeBar(RectangleShape &timeBar, float &timeOutTime, Time &dt, float &timeBarPixelPerSec, bool &timeOut, float &timeBarHeight)
{
    timeOutTime = timeOutTime - dt.asSeconds();
    float newTimeBarWidth = timeBarPixelPerSec * timeOutTime;
    if (newTimeBarWidth <= 0)
        timeOut = true;
    if (!timeOut)
        timeBar.setSize(Vector2f(newTimeBarWidth, timeBarHeight));
}

void updateBranch(Sprite *spriteBranch, int &chopHeight, int &maxBranch)
{
    for (int i = maxBranch - 1; i > 0; i--)
    {
        float x = spriteBranch[i - 1].getPosition().x;
        float y = spriteBranch[i - 1].getPosition().y;
        if (y > 900)
            y = -160;
        else
            y = y + chopHeight;
        spriteBranch[i].setPosition(x, y);
        spriteBranch[i].setRotation(spriteBranch[i - 1].getRotation());
    }
    float x = spriteBranch[0].getPosition().x;
    int choice = rand() % 3;
    if (choice == 0)
    {
        x = 1330;
        spriteBranch[0].setRotation(0);
    }
    else if (choice == 1)
    {
        x = 630;
        spriteBranch[0].setRotation(180);
    }
    else
    {
        x = 3000;
    }
    spriteBranch[0].setPosition(x, -160);
}

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Man !!!!");

    View view(FloatRect(0, 0, 1920, 1020));
    window.setView(view);

    Sprite spriteBackground;

    Texture textureBackground;
    textureBackground.loadFromFile("background.png");

    spriteBackground.setTexture(textureBackground);

    Sprite spriteCloud;
    Texture textureCloud;
    textureCloud.loadFromFile("cloud.png");
    spriteCloud.setTexture(textureCloud);
    spriteCloud.setPosition(0, 100);
    spriteCloud.setScale(0.8, 0.8);
    // bool moveCloud = false;
    float clodSpeed = 15;
    float pixelPerSecondCloud = 1920 / clodSpeed;

    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 150);
    float cloud1Speed = 10;
    float pixelPerSecondCloud1 = 1920 / cloud1Speed;

    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setPosition(0, 20);
    spriteCloud2.setScale(0.5, 0.5);
    float cloud2Speed = 25;
    float pixelPerSecondCloud2 = 1920 / cloud2Speed;

    Sprite spriteBee;
    Texture textureBee;
    textureBee.loadFromFile("bee.png");
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(1920, 880);
    // bool moveBee = false;
    float beeSpeed = 20;
    float pixelPerSecondBee = 1920 / beeSpeed;

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
    scoreMessage.setFillColor(Color::White);
    scoreMessage.setString("Score = 0");
    scoreMessage.setCharacterSize(100);
    scoreMessage.setPosition(100, 10);
    bool acceptInput = true;

    Text messageText;
    messageText.setFont(font);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start the game !!!!!");
    messageText.setCharacterSize(60);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    bool paused = true;

    bool timeOut = false;
    RectangleShape timeBar;
    float timeBarWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setOrigin(400 / 2, 80 / 2);
    timeBar.setPosition(1920 / 2, 880);

    float timeOutTime = 6;
    float timeBarPixelPerSec = timeBarWidth / timeOutTime;

    int maxBranch = 6;
    Sprite spriteBranch[6];
    Texture textureBranch;
    textureBranch.loadFromFile("branch.png");
    for (int i = 0; i < maxBranch; i++)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setPosition(3000, -260);
        spriteBranch[i].setOrigin(220, 40);
        spriteBranch[i].setRotation(180);
    }

    int chopHeight = 200;

    Sprite sprritePlayer;
    Texture texturePlayer;
    texturePlayer.loadFromFile("player.png");
    sprritePlayer.setTexture(texturePlayer);
    FloatRect bounds = sprritePlayer.getLocalBounds();
    sprritePlayer.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    sprritePlayer.setPosition(1310, 900 - bounds.height / 2.0f);

    bool gameOver = false;

    // sstream ss;

    Clock ct;
    Time dt;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased && acceptInput == false)
            {
                acceptInput = true;
            }
        }

        dt = ct.restart();
        if (!paused)
        {
            updateCloudSprite(spriteCloud, dt, pixelPerSecondCloud);
            updateCloudSprite(spriteCloud1, dt, pixelPerSecondCloud1);
            updateCloudSprite(spriteCloud2, dt, pixelPerSecondCloud2);
            updateBeeSprite(spriteBee, dt, pixelPerSecondBee);
            upadteTimeBar(timeBar, timeOutTime, dt, timeBarPixelPerSec, timeOut, timeBarHeight);
        }

        if (timeOut)
        {
            paused = true;
            messageText.setString("Time Out !!!!");
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                paused = !paused;
                if (paused == true)
                    messageText.setString("Game paused !!!");
                else
                    messageText.setString("");
                if (timeOut)
                {
                    timeOutTime = 6;
                    timeOut = false;
                    score_val = 0;
                }
                if (gameOver)
                {
                    timeOutTime = 6;
                    timeOut = false;
                    score_val = 0;
                    gameOver = false;
                    paused = false;
                    for (int i = 0; i < maxBranch; i++)
                    {
                        spriteBranch[i].setPosition(3000, -260);
                    }
                }
                acceptInput = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && !paused && !gameOver)
            {
                score_val++;
                timeOutTime = 6;

                updateBranch(spriteBranch, chopHeight, maxBranch);
                float y = sprritePlayer.getPosition().y;
                sprritePlayer.setPosition(810 - bounds.width / 2.0f - 10, y);
                sprritePlayer.setScale(-1.0f, 1.0f);
                acceptInput = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && !paused && !gameOver)
            {
                score_val++;
                timeOutTime = 6;
                updateBranch(spriteBranch, chopHeight, maxBranch);
                float y = sprritePlayer.getPosition().y;
                sprritePlayer.setPosition(810 + 300 + bounds.width / 2.0f + 10, y);
                sprritePlayer.setScale(1.0f, 1.0f);
                acceptInput = false;
            }
        }
        FloatRect playerBound = sprritePlayer.getGlobalBounds();
        FloatRect branchBound = spriteBranch[5].getGlobalBounds();
        if (playerBound.intersects(branchBound))
        {
            timeBar.setSize(Vector2f(0, 0));
            messageText.setString("Game OVER !!!!!!");
            paused = true;
            gameOver = true;
        }

        std::stringstream ss;
        ss << "Score = " << score_val;
        scoreMessage.setString(ss.str());

        FloatRect bounds = messageText.getLocalBounds();
        float mid_x = bounds.left + bounds.width / 2.0f;
        float mid_y = bounds.top + bounds.height / 2.0f;
        messageText.setOrigin(mid_x, mid_y);

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);

        window.draw(spriteTree);
        for (int i = 0; i < maxBranch; i++)
            window.draw(spriteBranch[i]);

        window.draw(sprritePlayer);

        window.draw(spriteBee);

        window.draw(scoreMessage);
        window.draw(messageText);
        window.draw(timeBar);

        window.display();
    }

    return (0);
}