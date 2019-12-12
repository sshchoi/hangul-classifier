# Korean Handwriting Classifier
### *by Seung Hoon Choi*

This project takes in handwritten Korean characters from the user through a GUI canvas and prints out the character the classifier analyzes the drawn image to be. 

#### System Requirements: 
You must have Xcode on MacOS to run this project. The program uses openFrameworks along with the following libraries: ofxOpenCv, ofxCv, and ofxGui.

#### How to Run:
Within the ofApp.cpp file in the src folder,
1. Uncomment line 32 to create the 2400 images training set with the preloaded 100 fonts in the fonts folder. Comment out line 32 ones all images are created.
2. Uncomment line 33 to create a text document with the probabilities of each pixel being shaded for each character. Then comment out line 33.
3. Finally, to check the classifier's accuracy, uncomment line 34. However, to simply use the program, run the main.cpp program with lines 32-34 commented out.

The GUI will pop up, where one can draw a character, then either click the "clear" button to clear out the canvas and redraw a character, or click the "analyze" button to have the program print out what character the classifier points the drawn image to be.
