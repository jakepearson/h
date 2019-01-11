# Automatically run the correct version of helm every time

This script will read the version of the Helm server you are running. It will then download a new version of `helm` if needed and run your command with new `helm`. I named it `h` since most everyone appears to alias `helm` to `h` anyway.

![So Simple](https://media.giphy.com/media/l4pTosVr0iHCJ11hm/giphy.gif)

## Getting Started

Download the file to somewhere in your path. Any time you would call `helm ...`, call `h ...` instead.

`curl -OL https://raw.githubusercontent.com/jakepearson/h/master/h && chmod +x h`
