#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// Set up the GUI and Fbo.
	ofBackground(0);
	
	gui.setup();
	gui.add(clear_button.setup("clear"));
	gui.add(analyze_button.setup("analyze"));
	
	fbo.allocate(kWindowSize, kWindowSize);
	fbo.begin();
	ofClear(0);
	fbo.end();

	// Setup the ofTrueTypeFont to print out the analyzed character.
	ofTrueTypeFontSettings settings(kFontPath + "/NanumSquare_acB.ttf", 20);
	settings.antialiased = true;
		
	// Allow for typing of Korean.
	settings.ranges = {
		ofAlphabet::Korean
	};

	// Loads TTF Settings into TTF.
	print.load(settings);
	
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––-––
	
//	H.CreateTrainingSet(kLabelsPath, kFontPath);								//<-- Use when needed.
//	CreateProbabilityModel();																		//<-- Use when needed.
//	TestModelAccuracy();																				//<-- Use when needed.
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Character: ", 30, 600);
	
	if(clear_button) {
		fbo.begin();
		ofClear(0);
		fbo.end();
		line = "";
	}
	
	if(analyze_button) {
		ofPixels myPixels;
		fbo.readToPixels(myPixels);
		
		ofImage image (myPixels);
		
		image.resize(28, 28);
		
		std::string folder_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/analyze/";
		
		std::string file_name = folder_path + "test.jpg";
		image.save(file_name);
		
		//------------------------------------------------------
		
		// Each image consists of 28x28 pixels.
		int i = 0, z = 0;
		
		std::vector<Image> a(1);
		
		ofImage img;
		if(img.load(file_name)) {
			img.setImageType(OF_IMAGE_GRAYSCALE);
			ofPixels &pixels = img.getPixels();
			
			for (int k = 0; k < IMAGE_SIZE; k++) {
				std::string line = "";
				for (int l = 0; l < IMAGE_SIZE; l++) {
					
					if(pixels[IMAGE_SIZE*k + l] > 180) {
						line.push_back('1');
					} else {
						line.push_back('0');
					}
				}
				a[0].image.push_back(line);
			}
			i++;
		}
		//-----------------------------------------------------
		
		//Creating 2D vector of probabilities of each class for each number in testing.
		std::string probability_model = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/probability_model.txt";
		std::vector<std::vector<double>> classification = MapClassification(probability_model, a, kLabelsPath);
		
		std::ifstream file("/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/labels.txt");
		GotoLine(file,PosteriorProbabilities(classification[0]));
		
		line = "";
		file >> line;
	}
	
	if(line.length() > 0) {
		ofSetColor(ofColor::white);
		print.drawString(line, 120, 605);
	}
	
	fbo.draw(0, 0);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// Same procedure as mousePressed, with placeholders for the parameters.
	ofApp::mousePressed(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	fbo.begin();
	ofSetColor(ofColor::white);
	ofDrawRectangle(mouseX-(kBrushSize/2),mouseY-(kBrushSize/2),kBrushSize,kBrushSize);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::CreateProbabilityModel() {
	std::vector<Image> training(NUM_TRAINING_IMAGES);
	std::string training_labels = kLabelsPath;
	std::string training_images = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/training_images/";
	
	//Filling training vector with images and labels that are connected through its classification.
	ImageVector(training_labels, training_images, training, kTrainingSize/kNumCharacters);
	ShadedProbability(training, training_labels);
}

//--------------------------------------------------------------
void ofApp::TestModelAccuracy() {
	//Creating a vector with each binary-converted image and label connected.
	std::vector<Image> testing(kTestingSize);
	
	ImageVector(kTestingLabelsPath, kTestingImagesPath, testing, kTestingSize/kNumCharacters);
	
	//Creating 2D vector of probabilities of each class for each number in testing.
	std::string probability_model = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/probability_model.txt";
	std::vector<std::vector<double>> classification = MapClassification(probability_model, testing,
																																			kLabelsPath);
	
	//Calculating accuracy of model.
	double num_correct = 0;
	for (int i = 0; i < testing.size(); i++) {
		
		std::ifstream file("/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/labels.txt");
		GotoLine(file,PosteriorProbabilities(classification[i]));
		
		std::string line;
		file >> line;
		
		//		std::cout << PosteriorProbabilities(classification[i]) << std::endl;
		
		if (line.compare(testing[i].classification) == 0) {
			num_correct++;
		}
	}
	
	std::cout << "Accuracy Percentage: " << (100 * (num_correct / testing.size())) << "%" << std::endl;
}
