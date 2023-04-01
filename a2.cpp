#include<iostream>
#include<cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gridlines();
bool check_collision(float, float, float, float);

Sprite* create_food(int);

const int gridlines(){

	srand(unsigned(time(0)));

	const int max = 99, min = 10, roll = 0440;

	int num = rand()%(max - min +1) + min;
	
	num *= 0; 		// last num of roll num is 0 

	int result = num / roll;
	result %= 25;


	if(result < 10){

	result += 15;
	}

	return result;
}

bool check_collision(float cor1x, float cor2x, float cor1y, float cor2y){

int size = 20;
int sizey = 40;

if((int)cor1x + size < (int)cor2x)
{
	return false;
}
if((int)cor2x + size < (int)cor1x){
	return false;
}
if((int)cor1y + sizey < (int)cor2y){
	return false;
}
if((int)cor2y + sizey < (int)cor1y){
	return false;
}

return true;
} 



Sprite* create_food(int size) {

		Sprite* food_arr = new Sprite[size - 5];
		return food_arr;
}



int main()
{   

	const int result = gridlines();

	const int size_of_block = 40;
	const int horizontal_end = 20;
	const int verticle_end = 50;

	RenderWindow window(VideoMode(750, 600), "ThreadGame");



//	LINES



	VertexArray line(Lines, 2*(result+result));

	for(int i =0; i< result; i++){

	line[i * 2].position = Vector2f(0.f, i * size_of_block);
    line[i * 2].color = Color::Black;
	line[(i*2)+1].position = sf::Vector2f(horizontal_end*size_of_block, i * size_of_block);
    line[(i*2)+1].color = sf::Color::Black;

	}

	for(int i =0; i< result; i++){

	line[2 * (i + result)].position = Vector2f(i * verticle_end, 0.f);
    line[2 * (i + result)].color = Color::Black;
	line[2 * (i + result)+1].position = sf::Vector2f(i * verticle_end, result * size_of_block);
    line[2 * (i + result)+1].color = sf::Color::Black;

	}


	
//	SPRITE

	Texture texture;
	if(!texture.loadFromFile("charachter.png")){

		cout<<"\nSprite ERROR!!!\n";

	}
	
	Texture texture2;
	if(!texture2.loadFromFile("charachter2.png")){

		cout<<"\nSprite2 ERROR!!!\n";

	}
	



/*

make array of sprites
create sprites
check collision with everyone
jidr jidr collision hui us array me bool 1 krdo
return structure object
in which it tells true at collision and the node at which the object collided
move the position of that node to unknown
collisions set

*/




	Sprite charachter(texture);
	charachter.setScale(Vector2f(60.f / texture.getSize().x, 60.f / texture.getSize().y));


	Sprite charachter2(texture2);
	charachter2.setScale(Vector2f(60.f / texture2.getSize().x, 60.f / texture2.getSize().y));
	charachter2.setPosition(550.f, 550.f);


	Sprite* food_arr = new Sprite[result - 5];

	food_arr = create_food(result);


	float Speedx = 100.f;
	float Speedy = 100.f;

	Clock clock;


	while (window.isOpen())
	{

		Time deltatime = clock.restart();
		float dt = deltatime.asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))
		{

		if(charachter.getPosition().x > 0 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
    	charachter.move( -Speedx * dt, 0.f);
		}
		else {
			charachter.move(-40 * dt, 0.f);
		}
		}


        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
		//cout<<charachter.getPosition().x<<"  "<<charachter2.getPosition().x<<endl;

		if(charachter.getPosition().x < 700 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y))
		{	
       	charachter.move( Speedx * dt, 0.f);
		}
		else {
			charachter.move(40 * dt, 0.f);
		}
        }


		if (Keyboard::isKeyPressed(Keyboard::Up))
        {
		if(charachter.getPosition().y > 0 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
       	charachter.move(0.f, -Speedy * dt);
        }
		else {
			charachter.move(0.f, -40 * dt);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
        {
		if(charachter.getPosition().y < 550 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
       	charachter.move(0.f, Speedy * dt);
		}
		else {
			charachter.move(0.f, 40 * dt);
		}
		}


// Player 2


		if (Keyboard::isKeyPressed(Keyboard::A))
		{
		if(charachter2.getPosition().x > 0 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move( -Speedx * dt, 0.f);
		}
		else {
			charachter2.move(-40 * dt, 0.f);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
		if(charachter2.getPosition().x < 700 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move( Speedx * dt, 0.f);
		}
		else {
			charachter2.move(40 * dt, 0.f);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
		if(charachter2.getPosition().y > 0 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move(0.f, -Speedy * dt);
		}
		else {
			charachter2.move(0.f, -40 * dt);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
		if(charachter2.getPosition().y < 550 && !check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move(0.f, Speedy * dt);
		}
		else {
			charachter2.move(0.f, 40 * dt);
		}
		}



 //   cout<<charachter.getPosition().x <<endl<<charachter.getPosition().y<<endl;

		window.clear(Color::White);
		window.draw(line);
		window.draw(charachter);
		window.draw(charachter2);
		window.display();
	}

}
