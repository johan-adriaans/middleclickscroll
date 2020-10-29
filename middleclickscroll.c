#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/Xatom.h>

Display *display;
Window root;

struct {
  float x;
  float y;
  unsigned int button_state;
} mouseinfo;

struct {
  float x;
  float y;
  float speed_x;
  float speed_y;
} scrollinfo;

#include "config.h"

void get_pointer();
void click_full(unsigned int button);
void scroll(float x, float y);
void init_x();
void close_x();

void get_pointer() {
  int x, y;
  int di;
  unsigned int dui;
  Window dummy;
  XQueryPointer(display, root, &dummy, &dummy, &x, &y, &di, &di, &dui);
  mouseinfo.x = x;
  mouseinfo.y = y;
  mouseinfo.button_state = dui;
}

void click_full(unsigned int button) {
  XTestFakeButtonEvent(display, button, 1, CurrentTime);
  XTestFakeButtonEvent(display, button, 0, CurrentTime);
  XFlush(display);
}

void scroll(float x, float y) {
  scrollinfo.x += x;
  scrollinfo.y += y;
  while (scrollinfo.y <= -0.51) {
    scrollinfo.y += 1;
    click_full(4);
  }
  while (scrollinfo.y >= 0.51) {
    scrollinfo.y -= 1;
    click_full(5);
  }
  while (scrollinfo.x <= -0.51) {
    scrollinfo.x += 1;
    click_full(6);
  }
  while (scrollinfo.x >= 0.51) {
    scrollinfo.x -= 1;
    click_full(7);
  }
}

void init_x() {
  display = XOpenDisplay((char *) 0);
	if (!display) {
		printf("Couldn't open display.\n");
		exit(EXIT_FAILURE);
	}
  int screen = DefaultScreen(display);
  root = RootWindow(display, screen);
}

void close_x(int exit_status) {
  XCloseDisplay(display);
  exit(exit_status);
}

int main () {
  init_x();

  get_pointer();

  scrollinfo.x = 0;
  scrollinfo.y = 0;
  scrollinfo.speed_x = 0;
  scrollinfo.speed_y = 0;

  float start_y;
  float start_x;
  unsigned int listening = 0;

  while (1) {
    get_pointer();

    // Use this to get the desired button mask
    //printf("Button state: %d\n", mouseinfo.button_state);

    if (mouseinfo.button_state & button_mask) {
      if (listening == 0) {
        start_y = mouseinfo.y;
        start_x = mouseinfo.x;
        XSetSelectionOwner (display, XA_PRIMARY, None, CurrentTime);
        listening = 1;
      }

      scrollinfo.speed_y = (mouseinfo.y - start_y) * speed * direction_x;
      scrollinfo.speed_x = (mouseinfo.x - start_x) * speed * direction_y;
      //printf("Scroll speed: %f\n", scrollinfo.speed_y);

      if (scrollinfo.speed_x != 0 || scrollinfo.speed_y != 0) {
        scroll(
          (float) scrollinfo.speed_x / move_rate,
          (float) scrollinfo.speed_y / move_rate
        );
      }
    } else {
      if (listening == 1) {
        listening = 0;
      }
    }
    usleep(1000000 / move_rate);
  }

  close_x(EXIT_SUCCESS);
}
