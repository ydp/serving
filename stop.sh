#!/bin/bash

ps -ef|grep tensorflow_model_server |grep -v grep | awk -F" " '{print $2}' | xargs kill
