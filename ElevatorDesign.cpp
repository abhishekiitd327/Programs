/*
 * ElevatorDesign.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: abhishkumar
 */
 #include <iostream>
#include <Windows.h>
#include <set>
#include <thread>
//#include <chrono>
#include <ctime>
using namespace std;

enum Direction_en {
	UP, DOWN
};
enum Status_en {
	MOVING, STOPPED
};

class Elevator {
	short _currFloor;
	short _nextFloor;
	Direction_en _dir;
	Status_en _status;
	set<short> _callingFloors;
public:
	Elevator(short cf, short nf, Direction_en d) :
			_currFloor(cf), _nextFloor(nf), _dir(d), _status(STOPPED) {
	}
	Elevator() :
			_currFloor(0), _nextFloor(0), _dir(UP), _status(STOPPED) {
	}
	~Elevator() {
		_callingFloors.clear();
	}
	void goToNextFloor() {
		_nextFloor = _currFloor;
		if (_dir == UP) {
			for (short floor : _callingFloors) {
				if (floor == _currFloor)
					_callingFloors.erase(_currFloor);
				if (floor > _nextFloor) {
					_nextFloor = floor;
					break;
				}
			}
			if (_nextFloor == _currFloor) { // going UP, but no floor above cur floor requested
				_dir = DOWN;
				_callingFloors.erase(_currFloor);
			}
		}
		if (_dir == DOWN) {
			set<short>::reverse_iterator floor;
			for (floor = _callingFloors.rbegin();
					floor != _callingFloors.rend(); ++floor) {
				if (*floor == _currFloor)
					_callingFloors.erase(_currFloor);
				if (*floor < _nextFloor) {
					_nextFloor = *floor;
					break;
				}
			}
			if (_nextFloor == _currFloor) {
				_dir = UP;
				_callingFloors.erase(_currFloor);
			} //else
			  //cout << "Next floor = " << _nextFloor << endl;
		}
	}
	void startLift() {
		_status = MOVING;
		goToNextFloor();
	}
	void stopLift() {
		_status = STOPPED;
	}
	void addFloor(short floor) {
		_callingFloors.insert(floor);
	}
	Status_en getStatus() const {
		return _status;
	}
	Direction_en getDirection() const {
		return _dir;
	}
	void run() {
		while (true) {
			if (this->_status == MOVING) {
				if (this->_dir == UP && _currFloor < _nextFloor) {
					clock_t c = clock();
					while (clock() - c < 1000) {
						;
					}
					_currFloor++;
					cout << _currFloor << endl;
				} else if (this->_dir == DOWN && _currFloor > _nextFloor) {
					clock_t c = clock();
					while (clock() - c < 1000) {
						;
					}
					_currFloor--;
					cout << _currFloor << endl;
				}
				if (_currFloor == _nextFloor) {
					_callingFloors.erase(_currFloor);
					cout << "Reached floor : " << _currFloor << endl;
					if (_callingFloors.empty()) {
						this->_status = STOPPED;
						break;
					} else
						goToNextFloor();
				}
			} // end if(status == MOVING)
		} // end while()
	} // end run()
};

class ElevatorManager {
	Elevator* _elevator;
public:
	ElevatorManager(Elevator* el) {
		_elevator = el; //new Elevator();
	}
	~ElevatorManager() {
		if (NULL != _elevator) {
			delete _elevator;
			_elevator = NULL;
		}
	}
	void pushButton(short floor) {
		cout << "Button " << floor << " pressed" << endl;
		_elevator->addFloor(floor);
		if (_elevator->getStatus() == STOPPED)
			_elevator->startLift();
		_elevator->goToNextFloor();
	}
};

int main() {
	cout << "... starting elevator" << endl;
	Elevator *el = new Elevator();
	thread t1(&Elevator::run, el);
	ElevatorManager em(el);
	em.pushButton(5);
	Sleep(1000); //std::this_thread::sleep_for(std::chrono::seconds(1));
	em.pushButton(9);
	em.pushButton(8);
	Sleep(2000); //std::this_thread::sleep_for(std::chrono::seconds(2));
	em.pushButton(1);
	em.pushButton(4);

	t1.join();
	cout << "Elevator Stopped ************ Exiting" << endl;

	return 0;
}
