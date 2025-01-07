#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    int correctOption; // 1-based index
};

struct Quiz {
    string title;
    vector<Question> questions;
};

map<string, int> results;

void createQuiz() {
    Quiz quiz;
    cout << "Enter quiz title: ";
    cin.ignore();
    getline(cin, quiz.title);

    int numQuestions;
    cout << "Enter the number of questions: ";
    cin >> numQuestions;

    for (int i = 0; i < numQuestions; ++i) {
        Question q;
        cout << "Enter question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, q.questionText);

        int numOptions;
        cout << "Enter the number of options: ";
        cin >> numOptions;

        for (int j = 0; j < numOptions; ++j) {
            string option;
            cout << "Enter option " << j + 1 << ": ";
            cin.ignore();
            getline(cin, option);
            q.options.push_back(option);
        }

        cout << "Enter the correct option (1-" << numOptions << "): ";
        cin >> q.correctOption;

        quiz.questions.push_back(q);
    }

    // Save quiz to file
    ofstream outFile(quiz.title + ".txt");
    if (outFile) {
        outFile << quiz.title << endl;
        outFile << quiz.questions.size() << endl;
        for (const auto& q : quiz.questions) {
            outFile << q.questionText << endl;
            outFile << q.options.size() << endl;
            for (const auto& opt : q.options) {
                outFile << opt << endl;
            }
            outFile << q.correctOption << endl;
        }
        cout << "Quiz saved successfully!\n";
    } else {
        cout << "Error saving the quiz.\n";
    }
}

void takeQuiz() {
    string title;
    cout << "Enter the quiz title to take: ";
    cin.ignore();
    getline(cin, title);

    ifstream inFile(title + ".txt");
    if (!inFile) {
        cout << "Quiz not found!\n";
        return;
    }

    Quiz quiz;
    getline(inFile, quiz.title);
    int numQuestions;
    inFile >> numQuestions;
    inFile.ignore();

    for (int i = 0; i < numQuestions; ++i) {
        Question q;
        getline(inFile, q.questionText);
        int numOptions;
        inFile >> numOptions;
        inFile.ignore();
        for (int j = 0; j < numOptions; ++j) {
            string option;
            getline(inFile, option);
            q.options.push_back(option);
        }
        inFile >> q.correctOption;
        inFile.ignore();
        quiz.questions.push_back(q);
    }

    // Start quiz
    int score = 0;
    for (int i = 0; i < quiz.questions.size(); ++i) {
        cout << "Question " << i + 1 << ": " << quiz.questions[i].questionText << endl;
        for (int j = 0; j < quiz.questions[i].options.size(); ++j) {
            cout << j + 1 << ". " << quiz.questions[i].options[j] << endl;
        }

        int answer;
        cout << "Enter your answer: ";
        cin >> answer;

        if (answer == quiz.questions[i].correctOption) {
            ++score;
        }
    }

    cout << "Quiz completed! Your score: " << score << "/" << quiz.questions.size() << endl;

    results[title] = score;
}

void viewResults() {
    if (results.empty()) {
        cout << "No results available.\n";
        return;
    }

    cout << "Quiz Results:\n";
    for (const auto& res : results) {
        cout << "Quiz: " << res.first << ", Score: " << res.second << endl;
    }
}

int main() {
    while (true) {
        cout << "\nQuiz Application\n";
        cout << "1. Create a Quiz\n";
        cout << "2. Take a Quiz\n";
        cout << "3. View Results\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            createQuiz();
            break;
        case 2:
            takeQuiz();
            break;
        case 3:
            viewResults();
            break;
        case 4:
            cout << "Exiting the application. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}