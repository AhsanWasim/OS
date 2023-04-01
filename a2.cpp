#include<iostream>
#include<cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gridlines();

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
	

	Sprite charachter(texture);
	charachter.setScale(Vector2f(50.f / texture.getSize().x, 40.f / texture.getSize().y));

	sf::Vector2f movement(0.f, 0.f);


	float Speedx = 50.f;
	float Speedy = 40.f;

	Clock clock;


	while (window.isOpen())
	{

		Time deltatime = clock.restart();
		float dt = deltatime.asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))
		{

    	charachter.move( -Speedx * dt, 0.f);

		}

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {

       	charachter.move( Speedx * dt, 0.f);
        }

		if (Keyboard::isKeyPressed(Keyboard::Up))
        {

       	charachter.move(0.f, -Speedy * dt);
        }
		if (Keyboard::isKeyPressed(Keyboard::Down))
        {

       	charachter.move(0.f, Speedy * dt);
        }

    
		window.clear(Color::White);
		window.draw(line);
		window.draw(charachter);
		window.display();
	}

}
