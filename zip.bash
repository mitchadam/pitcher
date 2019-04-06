#!/usr/bin/env bash

# This is what the tar archive will be called
TAR_NAME=pitcher.tar.gz

# Ignore .txt files in client
FILES="README Makefile hallelujah.wav src/* samples/*"

tar -czvf $TAR_NAME $FILES

echo "Thanks for zipping!"
