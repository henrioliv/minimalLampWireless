void update_palettes() {
  switch (palettes_mode) {
    case RETROWAVE:
      update_strip(duration, retrowave_palette);
      break;
    case RAINBOW:
      update_strip(duration, rainbow_palette);
      break;
    case PINK:
      update_strip(duration, pink_palette);
      break;
    case RED:
      update_strip(duration, red_palette);
      break;
    case ORANGE:
      update_strip(duration, orange_palette);
      break;
    case YELLOW:
      update_strip(duration, yellow_palette);
      break;
    case BROWN:
      update_strip(duration, brown_palette);
      break;
    case GREEN:
      update_strip(duration, green_palette);
      break;
    case CYAN:
      update_strip(duration, cyan_palette);
      break;
    case BLUE:
      update_strip(duration, blue_palette);
      break;
    case PURPLE:
      update_strip(duration, purple_palette);
      break;
    case WHITE:
      update_strip(duration, white_palette);
      break;
    case BLACK:
      update_strip(duration, black_palette);
      break;
    default:
      turn_off();
      break;
  }
}

void update_strip (int duration, uint8_t palette[][3]) {
  palette_reader(palette, line, red, green, blue);

  if (red + green + blue == 0) {
    line = 0;
  }
  else {
    line++;
    switch (animation_mode) {
      case OFF:
        turn_off();
        break;
      case COLORWIPE:
        colorWipe(strip.Color(red, green, blue),  duration);
        break;
      case CURTAINS:
        colorCurtains(strip.Color(red, green, blue),  duration);
        break;
      case DIAMONDS:
        colorDiamonds(strip.Color(red, green, blue),  duration);
        break;
      case RANDOM_DIAMONDS:
        colorRandomDiamonds(strip.Color(red, green, blue),  duration);
        break;
      case THEATER:
        theaterChase(strip.Color(red, green, blue), duration);
        break;
      default:
        turn_off();
        break;
    }
  }
}
