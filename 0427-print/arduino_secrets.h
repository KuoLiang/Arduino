#define SECRET_SSID "RyanRoy"
#define SECRET_PASS "klou802827"
#define APIKEY "SK2D5EZUZW0O4L9N"

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

// Thing Speak WRITE API KEY
const char* apiKey = APIKEY;
const char* resource = "/update?api_key=";
const char* server = "api.thingspeak.com";
