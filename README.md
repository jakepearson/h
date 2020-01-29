# Automatically run the correct version of helm every time

This script will read the version of the Helm server you are running, download a new version of the `helm` CLI to your machine if needed, and run your command with a version of `helm` that matches your server.

I named it `h` since most everyone appears to alias `helm` to `h` anyway.

![So Simple](https://media.giphy.com/media/l4pTosVr0iHCJ11hm/giphy.gif)

## Getting Started

Download the file to somewhere in your path. Any time you would call `helm ...`, call `h ...` instead.

`curl -OL https://raw.githubusercontent.com/jakepearson/h/master/h && chmod +x h`
