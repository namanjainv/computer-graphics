#!/bin/bash

shopt -s nullglob

rm -f hmwk_05
rm -f Tests/*results.*
rm -f Results/*results.*

echo "Compiling hmwk_04"
cd Answers
gcc -o ../hmwk_05 hmwk_05.c bezier.c line.c model.c projection.c triangle.c vertex.c view.c -lm
if [ $? != 0 ]
then
  echo "*** Compilation of hmwk_04.c failed."
  exit 1
fi

cd ..

for model in Tests/*.svfm
do
  mName=${model##*/}
  modelName=${mName%.svfm}

  echo -e "\n>>>>> Model ${modelName}"
  for view in Tests/${modelName}*.view
  do
    echo "  ${view}"

    settingNum=`echo "${view%.view}" | sed "s/Tests.${modelName}_setting_//g"`
    resultsSDF=Results/${modelName}_results_${settingNum}.sdf

    ./hmwk_05 $model $view > $resultsSDF
  done
done

