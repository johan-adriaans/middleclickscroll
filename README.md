# middleclickscroll
A tiny C program to enable middle click scrolling in X.

I use a Wacom tablet to control my linux machine and I was fed up with the fact that there was no decent way to scroll. I tried a few tools but none seemed to do what I wanted. During the search for new tools I stumbled upon [xmouseless](https://github.com/jbensmann/xmouseless), a tiny tool to control your mouse using your keyboard. It wasn't what I was after, but I got inspired and decided to borrow bits of their code to build something new. I am not a great C programmer, but I do have 20+ years experience in programming various other languages. If you are a C programmer and you see something weird, let me know and I will fix it. :)

## Features
* It polls your mouse button state and starts scrolling when your press the middle mouse (or any other mouse button/modifier).
* The scroll speed is defined by the distance from the point where you started pressing the button. Like autoscroll in firefox.
* The button, modifier key, scroll speed and scroll direction can be configured in config.h
* It auto clears your middle-mouse-paste buffer so you are not pasting selections all over the place.

## Installation

```
make
sudo make install
```

You will need to install some headers to build this. On debian based disros:
```
sudo apt-get install libx11-dev libxtst-dev
```

After installing (or just building) you can add it to your Gnome/KDE/X startup scripts.

## Configuration

The configuration is done in config.h, which is a C header file,
but you don't need any programming knowledge to edit it.
After you edited the file, you have to run make again.
