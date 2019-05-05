/*
 * Led.h
 *
 *  Created on: May 4, 2019
 *      Author: lasse
 */

#ifndef MAIN_LED_H_
#define MAIN_LED_H_

class Led
{
public:
	Led();
	virtual ~Led();
	void on();
	void off();
	void toggle();
};
#endif /* MAIN_LED_H_ */
