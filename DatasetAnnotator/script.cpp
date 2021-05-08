/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#include "scenario.h"
#include <string.h>
#include <direct.h>
#include <fstream>
#include "files.h"
#include <list>
#include <experimental/filesystem>
#include "keyboard.h"

DWORD	vehUpdateTime;
DWORD	pedUpdateTime;
using namespace std;
namespace fs = std::experimental::filesystem;


void record(std::ofstream& strm) {
	char path[] = "JTA\\";
	char scenarios_path[] = "JTA-Scenarios\\";
	// path for peds hash file
	char peds_path[] = "JTA-Peds\\";

	_mkdir(path);
	
	// redefined in the loop in order to change it based on the task
	//int max_samples = 30 * 60 * 1 + 1;
	// prova meno tempo
	//int max_samples = 60 * 10 * 1 + 1;
	int max_samples = 0;

	DatasetAnnotator* S;

	int seq_number = 0;
	// initialize peds number used to retrieve the file of the peds
	int peds_number = seq_number + 1;

	// task initialization
	char task[15] = "reID";
	bool secondCam = FALSE;
	int FPS;
	bool record_night = TRUE;
	bool wind = FALSE;

	std::ofstream ped_variations("ped_variations.txt");

	WAIT(1000);

	//// see if selected peds are visible
	//Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
	//// put the file admitted_peds.txt in the game folder first
	//std::ifstream admitted_peds("admitted_peds.txt");
	//Hash hash;
	//Ped tPed;
	//while (admitted_peds >> hash)
	//{
	//	STREAMING::REQUEST_MODEL(hash);
	//	WAIT(300);
	//	tPed = PED::CREATE_PED(26, hash, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//	for (int i = 0; i <= 11; i++) {
	//		PED::SET_PED_COMPONENT_VARIATION(tPed, i, 0, 0, 0);
	//	}
	//	strm << hash << " " << ENTITY::IS_ENTITY_VISIBLE(tPed) << "\n";
	//	WAIT(50);
	//	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	//	WAIT(300);
	//	PED::DELETE_PED(&tPed);
	//	WAIT(50);
	//}

	// Day sequences
	for (auto &p : fs::recursive_directory_iterator(scenarios_path)) {
		if (fs::is_regular_file(p)) {
			int nsamples = 0;

			//strm << seq_number << " " << peds_number << "\n";

			FILE *f = fopen(p.path().string().c_str(), "r");
			fscanf(f, "%d %d\n", &record_night, &wind);
			fscanf(f, "%s %*s %*s\n", task);
			fscanf(f, "%d", &secondCam);

			//strm << task << " " << secondCam << "\n";

			// resetting pointer of the file
			fseek(f, 0, SEEK_SET);

			if (secondCam)
				FPS = 60;
			else
				FPS = 30;

			std::string output_path = std::string(path) + std::string("seq_") + std::to_string(seq_number) + "_day_" + std::to_string(FPS);
			// name of the file for the peds
			std::string peds_file = std::string(peds_path) + "peds_" + std::to_string(peds_number) + ".txt";
			_mkdir(output_path.c_str());


			// 1 second video for debugging, put to 30 for final version
			max_samples = FPS * 30 * 1 + 1;
			//strm << FPS << task << max_samples << "\n";


			//S = new DatasetAnnotator(output_path, p.path().string().c_str(), max_samples, 0, task);
			S = new DatasetAnnotator(output_path, f, peds_file, max_samples, 0, task);

			Sleep(10);
			while (nsamples < max_samples) {
				nsamples = (*S).update();
				WAIT(0);
			}

			delete static_cast <DatasetAnnotator *>(S);
			seq_number++;

			peds_number++;

		}
	}

	// Night sequences
	seq_number = 0;
	peds_number = seq_number + 1;
	for (auto &p : fs::recursive_directory_iterator(scenarios_path)) {
		if (fs::is_regular_file(p)) {
			int nsamples = 0;

			strm << seq_number << " " << peds_number << "\n";

			FILE *f = fopen(p.path().string().c_str(), "r");
			fscanf(f, "%d %d\n", &record_night, &wind);
			if (!record_night) {
				fclose(f);
				seq_number++;
				peds_number;
				strm << seq_number << " " << peds_number << "\n";
				continue;
			}

			fscanf(f, "%s %*s %*s\n", task);
			fscanf(f, "%d", &secondCam);

			//strm << task << " " << secondCam << "\n";

			// resetting pointer of the file
			fseek(f, 0, SEEK_SET);

			if (secondCam)
				FPS = 60;
			else
				FPS = 30;

			std::string output_path = std::string(path) + std::string("seq_") + std::to_string(seq_number) + "_night_" + std::to_string(FPS);
			std::string peds_file = std::string(peds_path) + "peds_" + std::to_string(peds_number) + ".txt";
			_mkdir(output_path.c_str());

			max_samples = FPS * 30 * 1 + 1;

			S = new DatasetAnnotator(output_path, f, peds_file, max_samples, 1, task);
			
			Sleep(10);
			while (nsamples < max_samples) {
				nsamples = (*S).update();
				WAIT(0);
			}
			delete static_cast <DatasetAnnotator *>(S);
			seq_number++;

			peds_number++;
		}
	}

}


void main()
{	
	std::ofstream strm("logme.txt");
	while (true) {
		if (IsKeyJustUp(VK_F8)) {
			strm << "gg\n";
			record(strm);
		}
		WAIT(0);

	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
