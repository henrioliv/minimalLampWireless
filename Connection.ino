const char* ssid = "Pedro Batata";
const char* password = "xxxxxxxxx";

ESP8266WebServer server(80);

void handle_root() {
  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Following functions are available:<br><br>";
  message += "<a href='/con_animation_up'>Animation goes up</a> <br>";
  message += "<a href='/con_animation_down'>Animation goes down</a> <br><br>";

  message += "<a href='/con_speed_increased_a_lot'>Animation speed increases a lot</a> <br>";
  message += "<a href='/con_speed_increased'>Animation speed increases</a> <br>";
  message += "<a href='/con_speed_decreased'>Animation speed decreases</a> <br>";
  message += "<a href='/con_speed_decreased_a_lot'>Animation speed decreases a lot</a> <br><br>";

  message += "<a href='/con_pallete_up'>Pallete goes up</a> <br>";
  message += "<a href='/con_pallete_down'>Pallete goes down</a> <br><br>";

  message += "<a href='/con_brightness_up'>Brightness increases </a> <br>";
  message += "<a href='/con_brightness_down'>Brightness decreases </a> <br><br>";

  message += "<a href='/con_info'>See what is the current configuration </a> <br>";

  message += "****Minimalist Lamp Wireless****</body></html>";
  server.send(200, "text/html", message);
  message = "\0";
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void con_animation_up () {
  if (SERIAL_ON) {
    Serial.println("Animation Up");
  }
  animation_mode = animation_modes(animation_mode + 1);
  if (animation_mode >= number_of_modes) {
    animation_mode = animation_modes(1);
  }

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Animation went up!<br><br>";
  handle_page_update(message);
  message = "\0";
}
void con_animation_down () {
  if (SERIAL_ON) {
    Serial.println("Animation Down");
  }
  animation_mode  = animation_modes(animation_mode - 1);
  if (animation_mode <= 0) {
    animation_mode = animation_modes(number_of_modes - 1);
  }

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Animation went down!<br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_speed_increased () {
  if (SERIAL_ON) {
    Serial.println("Speed increased");
  }
  duration -= 5;
  if (duration < 25) {
    duration = 25;
  }

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Speed increased by 5ms!<br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_speed_decreased () {
  if (SERIAL_ON) {
    Serial.println("Speed decreased");
  }
  duration += 5;

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Speed decreased by 5ms!<br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_speed_increased_a_lot () {
  if (SERIAL_ON) {
    Serial.println("Speed increased a lot");
  }
  duration -= 100;
  if (duration < 25) {
    duration = 25;
  }

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Speed increased by 100ms<br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_speed_decreased_a_lot () {
  if (SERIAL_ON) {
    Serial.println("Speed decreased a lot");
  }
  duration += 100;

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Speed decreased by 100ms<br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_pallete_up () {
  if (SERIAL_ON) {
    Serial.println("Palette >>  ");
  }

  palettes_mode = palettes_modes(palettes_mode + 1);
  if (palettes_mode >= number_of_palettes) {
    palettes_mode = palettes_modes(0);
  }
  line = 0;

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>You selected a pallete above! <br><br>";
  handle_page_update(message);
  message = "\0";
}
void con_pallete_down () {
  if (SERIAL_ON) {
    Serial.println("Palette <<");
  }
  palettes_mode = palettes_modes(palettes_mode - 1);
  if (palettes_mode < 0) {
    palettes_mode = palettes_modes(number_of_palettes - 1);
  }
  line = 0;

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>You selected a pallete below! <br><br>";
  handle_page_update(message);
  message = "\0";
}

void con_brightness_up () {
  if (SERIAL_ON) {
    Serial.println("Brightness increased");
  }
  brightness += 10;
  if (brightness >= 255) {
    brightness = 255;
  }
  strip.setBrightness(brightness);

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Brightness increased +3% <br><br>";
  handle_page_update(message);
  message = "\0";
}
void con_brightness_down () {
  if (SERIAL_ON) {
    Serial.println("Brightness decreased");
  }
  brightness -= 10;
  if (brightness <= 0) {
    brightness = 1;
  }
  strip.setBrightness(brightness);

  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Brightness decreased -3% <br><br>";
  handle_page_update(message);
  message = "\0";
}

void handle_page_update(String message_beginning) {
  String message = message_beginning;

  message = "Current configuration is: <br>";
  message += "Animation mode: ";
  message += String(animation_mode);
  message += " <br>";

  message += "Pallet mode: ";
  message += String(palettes_mode);
  message += " <br>";

  message += "Brightness intensity: ";
  message += String(brightness);
  message += " <br>";

  message += "Update delay: ";
  message += String(duration);
  message += " <br>";

  message += "<a href='/'> Click here to go back to main menu</a></body></html>";
  server.send(200, "text/html", message);

  message = "\0";
}
