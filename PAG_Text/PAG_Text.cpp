#include "Navigator.h"
#include "SaveManager.h"

// Flow
int main() {
	try {
		SaveManager::InitSaveFiles();
		Navigator::GoToMainMenu();
	}
    catch (const std::exception& ex)
    {
        std::ofstream error_log("error_log.txt");
        error_log << "Exception: " << ex.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::ofstream error_log("error_log.txt");
        error_log << "Unknown exception occurred." << std::endl;
        return -1;
    }
    return 0;
}