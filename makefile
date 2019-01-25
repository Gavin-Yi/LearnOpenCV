main : main.o
	g++ -o main main.o -I /usr/local/include -I /usr/local/include/opencv -I /usr/local/include/opencv2 -L /usr/local/lib -l opencv_core -l opencv_highgui -l opencv_imgproc -l opencv_imgcodecs -l opencv_videoio
main.o : main.cpp
	g++ -g -c main.cpp
clean :
	rm main.o main 
