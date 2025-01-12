#!/bin/bash


for file in ~/graphs/networktest/*; do
{

./DemDS $file 1 1000 90 >> result-col

}
done





