// Build your own mask by adding these together (512 + 8 = alt-middle click)
// 1 = shift
// 2 = caps-lock
// 4 = control
// 8 = alt
// 16 = num-lock
// 256 = left click
// 512 = middle click
// 1024 = right click
static const int button_mask = 512;

// Vertical scroll direction
static const int direction_y = 1; // 1 = normal, -1 = invert, 0 = off

// Horizontal scroll direction
static const int direction_x = 1; // 1 = normal, -1 = invert, 0 = off

// Scrolling speed
static const float speed = 0.4;

// Speed of polling in hz (times per second)
static const unsigned int move_rate = 10;
