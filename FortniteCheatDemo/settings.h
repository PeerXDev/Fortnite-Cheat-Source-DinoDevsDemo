

#include "ExternalUtils.h"


float
TextSpaceLine = 90.f,
SpaceLineOne = 120.f,
SpaceLineTwo = 280.f,
SpaceLineThr = 420.f;

bool playerfly = false;
float bigbellynerds = 20.0f;

bool charge;
bool rapiddmr;

struct { //color configs
	float Black[3];
	float RGBRed[3] = { 1.0f, 0.0f, 0.0f };
	float RGBYelllow[3] = { 1.0f, 1.0f, 0.0f };
	float RGBGreen[3] = { 0.0f, 1.0f, 0.0f };
	float RGBBlue[3] = { 0.0f, 0.0f, 1.0f };
	float CMYKRed[3] = { 0.92f, 0.10f, 0.14f };
	float CMYKYellow[3] = { 1.0f, 0.94f, 0.0f };
	float CMYKGreen[3] = { 0.0f, 0.65f, 3.17f };
	float CMYKBlue[3] = { 0.18f, 0.19f, 0.57f };
	float PastelRed[3] = { 255.00f, 0.00f, 119.00f };
	float PastelRedOrange[3] = { 0.97f, 0.67f, 0.50f };
	float PastelYellowOrange[3] = { 0.99f, 0.77f, 0.53f };
	float PastelYellow[3] = { 1.0f, 0.96f, 0.6f };
	float PastelPeaGreen[3] = { 0.76f, 0.87f, 0.60f };
	float PastelYellowGreen[3] = { 0.63f, 0.82f, 0.61f };
	float PastelGreen[3] = { 0.50f, 0.79f, 0.61f };
	float PastelGreenCyan[3] = { 0.47f, 0.8f, 0.78f };
	float PastelCyan[3] = { 0.42f, 0.81f, 0.96f };
	float PastelCyanBlue[3] = { 0.49f, 0.65f, 0.85f };
	float PastelBlue[3] = { 0.51f, 0.57f, 0.79f };
	float PastelBlueViolet[3] = { 0.52f, 0.50f, 0.74f };
	float PastelViolet[3] = { 0.63f, 0.52f, 0.74f };
	float PastelVioletMagenta[3] = { 0.74f, 0.54f, 0.74f };
	float PastelMagenta[3] = { 0.95f, 0.60f, 0.75f };
	float PastelMagentaRed[3] = { 0.96f, 0.59f, 0.61f };
	float LightRed[3] = { 0.94f, 0.42f, 0.30f };
	float LightRedOrange[3] = { 0.96f, 0.55f, 0.33f };
	float LightYellowOrange[3] = { 0.98f, 0.68f, 0.36f };
	float LightYellow[3] = { 1.0f, 0.96f, 0.40f };
	float LightPeaGreen[3] = { 0.67f, 0.82f, 0.45f };
	float LightYellowGreen[3] = { 0.48f, 0.77f, 0.46f };
	float LightGreen[3] = { 0.23f, 0.72f, 0.47f };
	float LightGreenCyan[3] = { 0.10f, 0.73f, 0.70f };
	float LightCyan[3] = { 0.0f, 0.74f, 0.95f };
	float LightCyanBlue[3] = { 0.26f, 0.54f, 0.79f };
	float LightBlue[3] = { 0.33f, 0.45f, 0.72f };
	float LightBlueViolet[3] = { 0.37f, 0.36f, 0.65f };
	float LightViolet[3] = { 0.52f, 0.37f, 0.65f };
	float LightVioletMagenta[3] = { 0.65f, 0.39f, 0.65f };
	float LightMagenta[3] = { 0.94f, 0.43f, 0.66f };
	float LightMagentaRed[3] = { 0.94f, 0.42f, 0.49f };
	float Red[3] = { 0.92f, 0.10f, 0.14f };
	float RedOrange[3] = { 0.94f, 0.39f, 0.13f };
	float YellowOrange[3] = { 0.96f, 0.58f, 0.11f };
	float Yellow[3] = { 1.0f, 0.94f, 0.0f };
	float PeaGreen[3] = { 0.55f, 0.77f, 0.24f };
	float YellowGreen[3] = { 0.22f, 0.70f, 0.29f };
	float Green[3] = { 0.0f, 0.65f, 0.31f };
	float GreenCyan[3] = { 0.0f, 0.66f, 0.61f };
	float Cyan[3] = { 0.0f, 0.68f, 0.93f };
	float CyanBlue[3] = { 0.0f, 0.44f, 0.34f };
	float Blue[3] = { 0.0f, 0.32f, 0.65f };
	float BlueViolet[3] = { 0.19f, 0.19f, 0.57f };
	float Violet[3] = { 0.18f, 0.19f, 0.57f };
	float VioletMagenta[3] = { 0.57f, 0.15f, 5.63f };
	float Magenta[3] = { 0.92f, 0.0f, 0.54f };
	float MagentaRed[3] = { 0.92f, 0.07f, 0.35f };
	float DarkRed[3] = { 0.61f, 0.04f, 0.05f };
	float DarkROrange[3] = { 0.62f, 0.25f, 0.05f };
	float DarkYellowOrange[3] = { 0.53f, 0.38f, 0.03f };
	float DarkYellow[3] = { 0.67f, 0.62f, 0.0f };
	float DarkPeaGreen[3] = { 0.34f, 0.52f, 0.15f };
	float DarkYellowGreen[3] = { 0.09f, 0.48f, 0.18f };
	float DarkGreen[3] = { 0.0f, 0.44f, 0.21f };
	float DarkGreenCyan[3] = { 0.0f, 0.45f, 0.41f };
	float DarkCyan[3] = { 0.0f, 0.46f, 0.63f };
	float DarkCyanBlue[3] = { 0.0f, 0.29f, 0.50f };
	float DarkBlue[3] = { 0.0f, 0.20f, 0.44f };
	float DarkBlueViolet[3] = { 0.10f, 0.07f, 0.39f };
	float DarkViolet[3] = { 0.26f, 0.05f, 0.38f };
	float DarkVioletMagenta[3] = { 0.38f, 0.01f, 0.37f };
	float DarkMagenta[3] = { 0.61f, 0.0f, 0.36f };
	float DarkMagentaRed[3] = { 0.61f, 0.0f, 0.22f };
	float DarkerRed[3] = { 0.47f, 0.0f, 0.0f };
	float DarkerROrange[3] = { 0.48f, 0.18f, 0.0f };
	float DarkerYellowOrange[3] = { 0.49f, 0.28f, 0.0f };
	float DarkerYellow[3] = { 0.50f, 0.48f, 0.0f };
	float DarkerPeaGreen[3] = { 0.25f, 0.4f, 0.09f };
	float DarkerYellowGreen[3] = { 0.0f, 0.36f, 0.12f };
	float DarkerGreen[3] = { 0.0f, 0.34f, 0.14f };
	float DarkerGreenCyan[3] = { 0.0f, 0.34f, 0.32f };
	float DarkerCyan[3] = { 0.0f, 0.35f, 0.49f };
	float DarkerCyanBlue[3] = { 0.0f, 0.21f, 0.38f };
	float DarkerBlue[3] = { 0.0f, 0.12f, 0.34f };
	float DarkerBlueViolet[3] = { 0.05f, 0.0f, 0.29f };
	float DarkerViolet[3] = { 0.19f, 0.0f, 0.29f };
	float DarkerVioletMagenta[3] = { 0.29f, 0.0f, 0.28f };
	float DarkerMagenta[3] = { 0.48f, 0.0f, 0.27f };
	float DarkerMagentaRed[3] = { 0.47f, 0.27f, 0.14f };
	float PaleCoolBrown[3] = { 0.78f, 0.69f, 0.61f };
	float LightCoolBrown[3] = { 0.6f, 0.52f, 0.45f };
	float MiumCoolBrown[3] = { 0.45f, 0.38f, 0.34f };
	float DarkCoolBrown[3] = { 0.32f, 0.27f, 0.25f };
	float DarkerCoolBrown[3] = { 0.21f, 0.18f, 0.17f };
	float PaleWarmBrown[3] = { 0.77f, 0.61f, 0.43f };
	float LightWarmBrown[3] = { 0.65f, 0.48f, 0.32f };
	float MiumWarmBrown[3] = { 0.54f, 0.38f, 0.22f };
	float DarkWarmBrown[3] = { 0.45f, 0.29f, 0.14f };
	float DarkerWarmBrown[3] = { 0.37f, 0.22f, 0.07f };
	float purple[3] = { 144.00f, 0.00f, 255.00f };
	float white[3] = { 255.00f, 255.00f, 255.00f };
	float Sexycyan[3] = { 0.00f, 229.00f, 250.00f };
	float DarkestRed[3] = { 84.00f, 6.00f, 00.00f };
} color;

namespace Settings {
	float outline5[3] = { color.Black[0] , color.Black[1], color.Black[2] };
}


bool enemiesarround = true;
int enemyID = 0;
int enemyIDvis = 0;
int CloseRangeDistanceID = 0;
float CloseRangeDistance = 50.f;
float width = 0.5f;
bool InLobby;
float CachedFOV;

bool lootesp;
bool caresp;
bool chestesp;
bool stamina;
bool common{ false };

bool isLobby;
bool busnerds = false;
bool crouchingepse = false;
bool uncommon{ false };
bool rare{ false };
bool epic{ false };
bool legendary{ false };
bool mythic{ false };

bool vischeck = true;

bool exploits = false;
bool idkkk = false;

bool crouched = false;

bool fuel = false;
bool filledfov = false;
bool inffule = false;

bool teamcheck;

bool chams = false;

float BigPlayersScale = 2.50;


float espdistance = 100.f;


DWORD_PTR closestPawn = NULL;

bool weaponesp;
static int headnerds;
float Cached;
bool DynamicFov;
bool levelesp;
bool boxnerds = false;
bool killesp;
bool ShowMenu = true;
bool Smooth = false;
bool Esp = true;
Vector3 localactorpos;
bool stmaninerds = false;
bool vehiclefov = false;
Vector3 Location;
bool Esp_box = true;
static bool AnglesResetted = true;
bool ESPFOVCircle = false;
bool fovfill = false;
bool fovsquare = false;
int AimBoneInt;
bool sharkesp = false;
bool shieldcrates = false;
bool shieldesp = false;
bool floppaesp = false;
bool Esp_distance = false;
bool lamaesp = false;
bool Esp_fill = false;
bool vendingmachine = false;
bool invisible = false;
bool reloading = false;
bool radar;
bool Esp_crosshair = true;
double zoom;
bool Esp_line = false;
bool Esp_cline = false;
bool threeeeeed = false;
bool RandoAim = false;
float flRadarPos_x = 120;
float flRadarPos_y = 120;
float iSavedRadarX;
float iSavedRadarY;
bool box3d = false;
bool Esp_triangle = false;
int	RadarStyle = 0;
bool Esp_trifill = false;
bool topointfivehours = false;
bool Esp_teambox = false;
bool spinbot = false;
bool Esp_Skeleton = false;
bool rapidaug = false;
bool carfly = false;
bool while_rotating;
bool Esp_corner = false;
bool aimbotanimales = false;
bool bigplayers = false;
bool square = false;
bool crosshair = false;
bool supplycrate = false;
bool Bullettp = false;
bool AimNERD = false;
float lootnerddistance = 50.0f;
bool aimair = false;
bool niggerfovchanger = false;
bool pickheadpos = false;
int Spin = 0;
bool boatspeed = false;
bool instantreload = false;

bool carto = false;
bool circle = false;
bool Esp_Dot = false;
bool Aimbot = true;
bool speedvehicle = false;
bool Lock_Line = false;
bool memoryaim = false;
float bA1mb0tSm00th1ngV4lue = 3;
float FOVChangerValue = 81.0f;
bool debug = false;

bool instantreboot;

bool nazi = false;

bool isVis;

static int AimbotFOV = 150;
float wheredoweaim = 0;
int smooth = 5;


bool PlatFormEsp;
bool nameesp;
bool espnamenerds;
bool showteam = false;
bool animals;
bool activeweapon = false;
bool ammobox;
bool SuppyCrate;
bool ammmoesp;

bool targetlines = false;
bool platform;
bool nameeesp = false;

Vector3 LocalRelativeLocation;
uint64_t LocalRootcomp;

bool gravity = false;

static int aimkey;
bool samenrds;
static int aimlocataion;
static int hitbox;

float gravitynerds = 50.0f;


bool fly = false;

float boatmulti = 1.0f;

bool walk = false;
bool vehspooed = false;
bool IgnoreAllFallingDamage = false;
bool fastjump = false;
bool boatspeedd = false;
bool head;
bool chest;
bool pelvis;
bool legs;

namespace SettingsColor {
	static ImColor Esp;
	static ImColor Esp_Radar;
	static ImColor Esp_NotVisible;


}

namespace CachedCamera {
	double Pitch;
	double Yaw;
	uintptr_t ptr;
}

/*
*/