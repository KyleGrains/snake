#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

#include <curses.h>

#include "types.h"
#include "screen.h"


using namespace std::chrono_literals;

unsigned char input_character;
unsigned char processed_character;
unsigned char output_character;
std::mutex character_mutex;

constexpr std::chrono::milliseconds sleeptime(100ms);

int GetCharacter()
{
	return getch();
}

struct ReadInput{
	void operator()()
	{
		while(input_character = GetCharacter())
		{
			if(std::isprint(input_character))
			{
				std::lock_guard<std::mutex> character_mutex_guard(character_mutex);
				processed_character = input_character;
			}
			std::this_thread::sleep_for(sleeptime);
			if(input_character == 'q')
				break;
		}
	}
};

struct ProcessInput{
	void operator()()
	{
		std::unique_lock<std::mutex> character_mutex_lock(character_mutex);
		while(processed_character != 'q')
		{
			output_character = processed_character;
			std::cout << "y:" << output_character << std::flush;
			processed_character = ' ';
			character_mutex.unlock();
			std::this_thread::sleep_for(sleeptime);
			character_mutex.lock();
		}
	}
};

int main()
{
  InitScreen();

	std::thread tReadInput((ReadInput()));
	std::thread tProcessInput((ProcessInput()));

	tReadInput.join();
	tProcessInput.join();

	UninitScreen();
  return 0;
}

