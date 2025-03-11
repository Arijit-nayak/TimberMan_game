#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
VideoMode vm(200,200);
RenderWindow window(vm, "Timber Man");

Sprite spriteBackground;
Texture textureBackground;
textureBackground.loadFromFile("background.png");
spriteBackground.setTexture(textureBackground);


while (window.isOpen())
{
window.clear();
window.draw(spriteBackground);
window.display();
}
return 0;
}