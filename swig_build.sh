#mkdir -p build/generated-src/java

#You need to checkout sphinxbase, pocketsphinx and Testpocketsphinx and put them in the same folder
#the install tutorial of sphinxbase and pocketsphibx http://jrmeyer.github.io/installation/2016/01/09/Installing-CMU-Sphinx-on-Ubuntu.html
#replace sphinxbase/swig/sphinxbase.i with Testpocketsphinx/jni/sphinxbase.i
#replace pocketsphinx/swig/pocketsphinx.i with Testpocketsphinx/jni/pocketsphinx.i
#the swig order

#swig sphinxbase_i
swig -I../sphinxbase/include -I../sphinxbase/swig -java -package com.midea.VadAsr -outdir src/com/midea/VadAsr -o jni/sphinxbase_wrap.c ../sphinxbase/swig/sphinxbase.i

#swig pocketsphinx_i
swig -I../sphinxbase/swig -I../pocketsphinx/include -I../pocketsphinx/swig -java -package com.midea.VadAsr -outdir src/com/midea/VadAsr -o jni/pocketsphinx_wrap.c ../pocketsphinx/swig/pocketsphinx.i

#swig will generate jni/sphinxbase_wrap.c and jni/pocketsphinx_wrap.c
#and the .java file in src/com/example/testpocketsphinx/swig

#then cd jni
#run ndk-build
#this order will generate *so in libs/*/
