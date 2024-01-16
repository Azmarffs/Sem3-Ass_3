#include <iostream>
#include <fstream>
#include"header.h"
using namespace std;
int main() {
    FileDirectoryTree fileSystem;

    string rootName;
    cout << "Enter the root name: ";
    cin >> rootName;

    fileSystem.setRootName(rootName);

    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Add a directory\n";
        cout << "2. Add a file\n";
        cout << "3. Delete a file or directory\n";
        cout << "4. Merge directories\n";
        cout << "5. Search For file" << endl;
        cout << "6. Search For Directory" << endl;
        cout << "7. Copy Node to a new location\n";
        cout << "8. Export to File\n";
        cout << "9. Import from File\n";
        cout << "10. List the tree\n";
        cout << "11. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string dirName, parentPath;
                cout << "Enter the directory name: ";
                cin >> dirName;
                cout << "Enter the parent path (in the current path): ";
                cin >> parentPath;

                fileSystem.createDirectory(dirName, "/" + parentPath + dirName);
                break;
            }
            case 2: {
                string fileName, fileType, dirName;
                cout << "Enter the file name: ";
                cin >> fileName;
                cout << "Enter the file type: ";
                cin >> fileType;
                cout << "Enter the parent path (in the current path): ";
                cin >> dirName;

                fileSystem.createFile(fileName, fileType, "/" + rootName + dirName);
                break;
            }
            case 3: {
                string name, parentPath;
                cout << "Enter the name of the file to delete: ";
                cin >> name;
                cout << "Enter the parent path of the file or directory to delete: ";
                cin >> parentPath;

                fileSystem.deleteNode(parentPath, name); // Modify this line to pass two arguments
                break;
            }
            case 4: {
                fileSystem.mergeDirectories(fileSystem);
                break;
            }
            case 5: {
                string fileName;
                cout << "Enter the file name to search: ";
                cin >> fileName;

                // Initialize fileNode to nullptr
                TreeNode* fileNode = nullptr;

                // Call the searchFile function with the fileNode parameter
                fileSystem.searchFile(fileSystem.getRoot(), fileName, fileNode);

                if (fileNode == nullptr) {
                    cout << "File " << fileName << " not found!\n";
                }
                break;
                
            }
            case 6: {
                string dirName;
                cout << "Enter the directory name to search: ";
                cin >> dirName;

                if (fileSystem.searchDirectory(fileSystem.getRoot(), dirName)) {
                    cout << "True\n";
                } else {
                    cout << "False\n";
                }
                break;
            }
            case 7: {
                string fileName, fileType, dirName;
                cout << "Enter the file name you want to copy: ";
                cin >> fileName;
                cout << "Of what type that file is that you want to copy?: ";
                cin >> fileType;
                cout << "Give the path of directory to which you want to copy that file: ";
                cin >> dirName;

                fileSystem.createFile(fileName, fileType, "/" + rootName + dirName);

                cout << "Do you want to delete the file from orginal location? (Y/N): ";
                char choice;
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    cout << "Give the path for original directory: ";
                    cin >> dirName;
                    fileSystem.deleteNode(dirName, fileName);

                }
                
                break;
            }
            case 8: {
                ofstream file("BSTtree.txt");
                fileSystem.exportTreeToFile(fileSystem.getRoot(), file);
                file.close();
                break;
            }
            case 9: {
                ifstream file("BSTtree.txt");
                fileSystem.importTreeFromFile(fileSystem.getRoot(), file);
                file.close();
                break;
               
            }
            case 10: {
                fileSystem.listTree();
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
