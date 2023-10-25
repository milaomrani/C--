#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#else
#include <sys/stat.h>
#endif
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>




int main() {
    // Load the pre-trained Haar Cascade classifier for face detection
    cv::CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_default.xml");

    // Open a video stream (0 for the default camera, or specify a file path)
    cv::VideoCapture video(0);

    if (!video.isOpened()) {
        std::cerr << "Error: Unable to open video stream or file." << std::endl;
        return -1;
    }

    // create folderes named detected_faces
    struct stat st = { 0 };
    if (stat("detected_faces", &st) == -1) {
        mkdir("detected_faces", 0700);
    }

    // create a folder named face_data
    if (stat("face_data", &st) == -1) {
        mkdir("face_data", 0700);
    }

    while (true) {
        cv::Mat frame;
        video >> frame;

        if (frame.empty()) {
            std::cerr << "End of video stream or file." << std::endl;
            break;
        }

        // Convert the frame to grayscale for face detection
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Draw rectangles around detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Crop the face and save it in a folder called detected faces
        cv::Mat cropFace;
        for (const auto& face : faces) {
            cropFace = frame(face);
        }

        // if face detected, save frame in a folder called detected faces. 
        if (faces.size() > 0) {
            cv::imwrite("detected_faces/" + std::to_string(time(nullptr)) + ".jpg", cropFace);
            // save face data (x, y, width and height) in a text file corresponding to the image name
            std::ofstream file("face_data/" + std::to_string(time(nullptr)) + ".txt");
            for (const auto& face : faces) {
                file << face.x << " " << face.y << " " << face.width << " " << face.height << std::endl;
            }
            file.close();
        }
       
        
        // Display the frame with detected faces
        cv::imshow("Face Detection", frame);

        // Exit the loop when the user presses the 'q' key
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}


// docker run -it --name my_cpp_container my_cpp_app
