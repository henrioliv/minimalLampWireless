void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

  strip.setBrightness(brightness); // Set BRIGHTNESS (max = 255)

  pinMode(LED_INFO_PIN, OUTPUT);   //Configuring LEDs for feedback

  if (SERIAL_ON) {
    Serial.begin(115200);
    Serial.println("\n****Minimalist Lamp Wireless****\n");
  }

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (SERIAL_ON) {
      Serial.print(".");
    }
    digitalWrite(LED_INFO_PIN, led_info_pin);
    led_info_pin = !led_info_pin;
  }
  digitalWrite(LED_INFO_PIN, LOW);
  delay(2000);
  if ( SERIAL_ON) {
    Serial.print("\nConnected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  // Server pages
  server.on("/", handle_root);
  server.on("/con_animation_up", con_animation_up);
  server.on("/con_animation_down", con_animation_down);

  server.on("/con_speed_increased", con_speed_increased);
  server.on("/con_speed_decreased", con_speed_decreased);
  server.on("/con_speed_increased_a_lot", con_speed_increased_a_lot);
  server.on("/con_speed_decreased_a_lot", con_speed_decreased_a_lot);

  server.on("/con_pallete_up", con_pallete_up);
  server.on("/con_pallete_down", con_pallete_down);

  server.on("/con_brightness_up", con_brightness_up);
  server.on("/con_brightness_down", con_brightness_down);

  server.on("/con_info", []() {
    String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Hope you are enjoying your lamp! <br><br>";
    handle_page_update(message);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  animation_mode = animation_modes(random(1, number_of_modes));
  duration = 200;
  palettes_mode = palettes_modes(random(0, number_of_palettes));

  if (SERIAL_ON) {
    Serial.println("HTTP server started");
    Serial.println("Starting the lamp with a random configuration");
    Serial.println("\nCurrent setup is\n");
    Serial.print("Brigthness \t\t");
    Serial.print(brightness);
    Serial.println("/255");
    Serial.print("Update period \t\t");
    Serial.print(duration);
    Serial.println(" ms");
    Serial.print("Selected Pallet \t");
    Serial.println(palettes_modes(palettes_mode));
    Serial.print("Selected animation \t");
    Serial.println(animation_mode);
  }

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  ticker_server.attach(2, led_update);
}

void loop() {
  update_palettes();
  server.handleClient();
}

void led_update() {
  digitalWrite(LED_INFO_PIN, led_info_pin);
  led_info_pin = !led_info_pin;
}
