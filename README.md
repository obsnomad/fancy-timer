# Fancy timer
This is the timer application built on Qt which displays fullscreen timer with background image and music. Can be used on games and other stuff.

## Functionality
When started the application show timer clock counting down to zero. Music plays during counting (if configured) and stops at zero. Alarm beeping sound appears on the alarm breakpoint (if configured) and another "final" sound plays at zero (if configured). To exit the application hit Alt+F4 or ESC.

## Configuration
All configuration values can be set in config.ini file of application root. Here is the example of the file:
```ini
# Background image (relative or absolute path)
BACKGROUND_IMAGE=
# Background color (default is white)
BACKGROUND_COLOR=#113b7c
# Font color (default is black, not necessary for now may be implemented later)
FONT_COLOR=#fff
# Background music
MUSIC=src/audio.mp3
# Alarm beeping sound
ALARM=src/beep.mp3
# Sound at 0 seconds
FINAL=src/badum.mp3
# Timer font family (default is system font)
TIMER_FONT_FAMILY=Courier
# Timer font size (default is 150)
TIMER_FONT_SIZE=300
# Timer font thickness (0 - normal, 1 - bold, default is 0)
TIMER_FONT_BOLD=1
# Timer font color (default is equal to FONT_COLOR)
TIMER_FONT_COLOR=
# Timer font color when alarm breakpoint is reached
TIMER_FONT_COLOR_ALARM=#ff0
# Timer start (value) value in seconds (default is 60)
TIMER_DEFAULT_VALUE=60
# Alarm breakpoint value in seconds (default is -1 - which is none)
TIMER_ALARM_VALUE=10
```
If you need several time options then you can create links for program as follows:
```bash
{path_to_application}/Timer [default_value] [alarm_value]
```
If two arguments are stated then application use both of them. If only one argument is stated then application uses alarm breakpoint from configuration file.
