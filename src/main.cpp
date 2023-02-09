#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

int main() {
  // Initialize the SFML window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML & Box2D Example");

  // Create a Box2D world
  b2Vec2 gravity(0.0f, 9.8f);
  b2World world(gravity);

  // Define a Box2D body
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  b2Body* body = world.CreateBody(&bodyDef);

  // Define a Box2D shape
  b2PolygonShape shape;
  shape.SetAsBox(1.0f, 1.0f);

  // Define a Box2D fixture
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  body->CreateFixture(&fixtureDef);

  // Create a SFML circle shape to represent the Box2D body
  sf::CircleShape circle(50.0f);
  circle.setFillColor(sf::Color::Red);
  circle.setOrigin(50.0f, 50.0f);

  // Main loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // Update the Box2D world
    float timeStep = 1.0f / 60.0f;
    int velocityIterations = 6;
    int positionIterations = 2;
    world.Step(timeStep / 8, velocityIterations, positionIterations);

    // Update the position of the SFML circle to match the Box2D body
    b2Vec2 position = body->GetPosition();
    std::cout << position.x << " " << position.y << std::endl;
    circle.setPosition(400, position.y);
    
    if (position.y >= 400)
    {
    circle.setPosition(400, 400);
    }

    // Clear the window and draw the SFML circle
    window.clear();
    window.draw(circle);
    window.display();
  }

  return 0;
}

