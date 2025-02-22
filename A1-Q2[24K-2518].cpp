#include <iostream>
#include <string>

using namespace std;

class Ball {
private:
    int x, y;
public:
    Ball(int startX, int startY) : x(startX), y(startY) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void move(int dx, int dy) { x += dx; y += dy; }
    void getPosition(int &posX, int &posY) const { posX = x; posY = y; }
    void resetPosition(int startX, int startY) { x = startX; y = startY; }
};

class Goal {
private:
    int x, y;
public:
    Goal(int goalX, int goalY) : x(goalX), y(goalY) {}
    bool isGoalReached(int ballX, int ballY) const { return x == ballX && y == ballY; }
};

class Robot {
private:
    string name;
    int hits;
public:
    Robot(string robotName) : name(robotName), hits(0) {}
    void hitBall(Ball &ball, const string &direction) {
        if (direction == "up") ball.move(0, 1);
        else if (direction == "down") ball.move(0, -1);
        else if (direction == "left") ball.move(-1, 0);
        else if (direction == "right") ball.move(1, 0);
        hits++;
    }
    int getHits() const { return hits; }
};

class Team {
private:
    string teamName;
    Robot *robot;
public:
    Team(string name, Robot *robotPlayer) : teamName(name), robot(robotPlayer) {}
    Robot* getRobot() const { return robot; }
    string getTeamName() const { return teamName; }
};

class Game {
private:
    Team *teamOne;
    Team *teamTwo;
    Ball ball;
    Goal goal;
public:
    Game(Team *t1, Team *t2, Ball b, Goal g) : teamOne(t1), teamTwo(t2), ball(b), goal(g) {}
    void startGame() {
        play(teamOne);
        ball.resetPosition(0, 0);
        play(teamTwo);
        declareWinner();
    }
    void play(Team *team) {
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            string direction;
            cout << team->getTeamName() << " - Enter direction (up, down, left, right): ";
            cin >> direction;
            team->getRobot()->hitBall(ball, direction);
            int x, y;
            ball.getPosition(x, y);
            cout << "Ball position: (" << x << ", " << y << ")\n";
        }
        cout << team->getTeamName() << " reached the goal in " << team->getRobot()->getHits() << " hits.\n";
    }
    void declareWinner() {
        int hitsOne = teamOne->getRobot()->getHits();
        int hitsTwo = teamTwo->getRobot()->getHits();
        if (hitsOne < hitsTwo) {
            cout << teamOne->getTeamName() << " wins!\n";
        } else if (hitsTwo < hitsOne) {
            cout << teamTwo->getTeamName() << " wins!\n";
        } else {
            cout << "It's a tie!\n";
        }
    }
};

int main() {
    Robot robot1("Robot1");
    Robot robot2("Robot2");
    Team teamOne("TeamOne", &robot1);
    Team teamTwo("TeamTwo", &robot2);
    Ball ball(0, 0);
    Goal goal(3, 3);
    Game game(&teamOne, &teamTwo, ball, goal);
    game.startGame();
    return 0;
}