include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(600, 600), "Bong Game", Style::Close | Style::Resize);

    float xvelocityball = -0.3;
    float yvelocityball = -0.3;
    int right_fail = 0;
    int left_fail = 0;
    int right_score = 0;
    int left_score = 0;

    CircleShape ball;
    ball.setFillColor(Color::Red);
    ball.setRadius(10);
    ball.setPosition(500, 400);

    RectangleShape right;
    right.setSize(Vector2f(15, 50));
    right.setFillColor(Color::Green);
    right.setPosition(585.f, 250.f);

    RectangleShape left;
    left.setSize(Vector2f(15, 50));
   left.setFillColor(Color::Green);
   left.setPosition(0.f, 250.f);

   while (window.isOpen())
   {
       Event evnt;
       while (window.pollEvent(evnt))
       {
           switch (evnt.type) {
           case Event::Closed:
               window.close();
               break;
           case Event::Resized:
               cout << "the width " << evnt.size.width << endl << "the haight " << evnt.size.height << endl;
               break;
           case Event::TextEntered:
               if (evnt.text.unicode < 120)
                   cout << evnt.text.unicode;
           }
        }
       //RectangleShape movement
       if (Keyboard::isKeyPressed(Keyboard::Key::W))
       {
           left.move(0.f, -1.0f);
       }
       if (Keyboard::isKeyPressed(Keyboard::Key::S))
       {
           left.move(0.0f, 1.0f);
       }
       if (Keyboard::isKeyPressed(Keyboard::Key::Up))
       {
           right.move(0.0f, -1.0f);
       }
       if (Keyboard::isKeyPressed(Keyboard::Key::Down))
       {
           right.move(0.00f, 1.0f);
       }

       //RectangleShape collision
       if (left.getPosition().y < 0.f)
       {
           left.setPosition(left.getPosition().x, 0.f);
       }
       if (right.getPosition().y < 0.f)
       {
           right.setPosition(right.getPosition().x, 0.f);
       }
       if (right.getPosition().y > 550.f)
       {
           right.setPosition(right.getPosition().x, 550.f);
       }
       if (left.getPosition().y > 550.f)
       {
           left.setPosition(left.getPosition().x, 550.f);
       }

       //ballmovement
       if (left_fail < 5 && right_fail < 5)
       {
           ball.move(xvelocityball, yvelocityball);
           if (ball.getPosition().y < 0 || ball.getPosition().y > 580)
           {
               yvelocityball *= -1;
           }
           else if (ball.getGlobalBounds().intersects(left.getGlobalBounds()))
           {
               xvelocityball *= -1;
               left_score++;
               xvelocityball += 0.2;
               yvelocityball += 0.2;
           }
           else if (ball.getGlobalBounds().intersects(right.getGlobalBounds()))
           {
               xvelocityball *= -1;
               right_score++;
               xvelocityball += 0.05;
               yvelocityball += 0.05;
           }
           if (ball.getPosition().x < 0)
           {
               ball.setPosition(200.f, 200.f);
               left_fail++;
               xvelocityball = -0.3;
               yvelocityball = -0.3;
           }
           else if (ball.getPosition().x > 580)
           {
               ball.setPosition(200.f, 200.f);
               right_fail++;
               xvelocityball = -0.3;
               yvelocityball = -0.3;
           }
       }
       else
       {
           window.close();
       }

       window.clear();
       window.draw(right);
        window.draw(left);
      window.draw(ball);
        window.display();
    }

    return 0;
}
