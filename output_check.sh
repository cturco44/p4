#!/bin/bash

#  output_check.sh
#  p4
#
#  Created by Connor Turco on 6/19/20.
#  Copyright © 2020 Connor Turco. All rights reserved.
make poke
echo ======================= Spec Test ======================================
./poke -m OPTTSP < spec-test.txt > testy.txt


