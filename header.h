                    /*
                    Name: Azmar Kashif
                    Section: B
                    Roll No: 22i-2716
                    */                    
#include <iostream>
#include <fstream>

using namespace std;

class TreeNode {
public:
    string name;
    string path;
    string type; // file type, empty for directory
    TreeNode* left;
    TreeNode* right;

    TreeNode(string name, string path, string type)
        : name(name), path(path), type(type), left(nullptr), right(nullptr) {}
};

class FileDirectoryTree {
    TreeNode* root;
    string rootName;
    public:
    TreeNode* createNode(string name, string path, string type) {
        return new TreeNode(name, path, type);
    }

    TreeNode* createDirectory(TreeNode* node, string name, string fullPath) {
        if (node == nullptr) {
            size_t lastSlash = fullPath.find_last_of('/'); // Find the last slash in the full path
            string parentPath = fullPath.substr(0, lastSlash); // Extract the parent path from the full path

            if (parentPath.empty()) {
                // This is the first directory after the root
                return createNode(name, "/" + name, ""); //line to set the path
            } else {
                return createNode(name, fullPath, ""); //  line to set the path
            }
        }

        if (fullPath < node->path) { //  line to compare only the relative path
            node->left = createDirectory(node->left, name, fullPath); //  line to pass the fullPath parameter
        } else if (fullPath > node->path) {
            node->right = createDirectory(node->right, name, fullPath); //  line to pass the fullPath parameter  
        } else {
            // Directory with the same path already exists
            if (!node->type.empty()) { //  line to check if the node is a file
                // There is a file associated with this directory, add the new directory under the file
                node->right = createDirectory(node->right, name, node->path + "/" + name); // line to pass the fullPath parameter
            } else {
                // There is no file associated with this directory, just add the new directory
                node->left = createDirectory(node->left, name, fullPath); //  line to pass the fullPath parameter
            }
        }
        return node;
    }

    TreeNode* createFile(TreeNode* node, string name, string type, string fullPath) {
        if (type != "pdf" && type != "txt") {
            cout << "Invalid file type! Only 'pdf' and 'txt' file types are allowed.\n";
            return node;
        }
        if (node == nullptr) {
            return createNode(name, fullPath, type);
        }

        if (fullPath < node->path) { //  line to compare only the relative path
            node->left = createFile(node->left, name, type, fullPath); //  line to pass the fullPath parameter
        } else if (fullPath > node->path) {
            node->right = createFile(node->right, name, type, fullPath); //  line to pass the fullPath parameter
        }
        return node;
    }

    void listTree(TreeNode* node, int depth = 0) {
        const int INDENT_SIZE = 4; //  line to set the indentation size

        if (node != nullptr) {
            listTree(node->left, depth + 1); //  line to pass the depth parameter

            for (int i = 0; i < depth * INDENT_SIZE; ++i) {  //  line to set the indentation
                cout << " ";
            }

            cout << "|__ " << node->name;

            if (!node->type.empty()) { //  line to check if the node is a file
                cout << " -> (" << node->type << ")\n";
            } else {
                cout << " -> (Directory)\n";
            }

            listTree(node->right, depth + 1); //  line to pass the depth parameter
        }
    }


    TreeNode* findNode(TreeNode* node, const string& path) {
        if (node == nullptr) {
            return nullptr;
        }

        // Adjust the comparison to consider only the relative path
        size_t lastSlash = path.find_last_of('/');
        string relativePath = path.substr(lastSlash + 1); //  line to extract the relative path

        if (node->name == relativePath) { //  line to compare only the relative path
            return node;
        }

        TreeNode* leftResult = findNode(node->left, path); //  line to pass the path parameter
        if (leftResult != nullptr) { //  line to check if the node is not null
            return leftResult;
        }

        TreeNode* rightResult = findNode(node->right, path); //  line to pass the path parameter
        return rightResult;
    }

    TreeNode* inorderSuccessor(TreeNode* node) {
        TreeNode* current = node;

        while (current && current->left != nullptr) { //  line to check if the current node is not null
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* node, string name, string fullPath) {
        if (node == nullptr) {
            return node;
        }

        if (fullPath < node->path) { //  line to compare only the relative path
            node->left = deleteNode(node->left, name, fullPath);
        } else if (fullPath > node->path) { //  line to compare only the relative path
            node->right = deleteNode(node->right, name, fullPath);
        } else {
            // Node with the specified path found
            if (node->name == name) { //  line to compare only the relative path
                // Node to delete found
                if (node->left == nullptr) { //  line to check if the left node is null
                    TreeNode* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) { //  line to check if the right node is null
                    TreeNode* temp = node->left;
                    delete node;
                    return temp;
                }

                TreeNode* temp = inorderSuccessor(node->right); //  line to pass the node->right parameter
                node->name = temp->name;
                node->path = temp->path;
                node->type = temp->type;
                node->right = deleteNode(node->right, temp->name, temp->path);  //  line to pass the temp->name and temp->path parameter
            } else {
                node->right = deleteNode(node->right, name, fullPath); //  line to pass the fullPath parameter
            }
        }
        return node;
    }

    void move(TreeNode* source, TreeNode* destination) {
        if (destination->left == nullptr) { //  line to check if the left node is null
            destination->left = source; //  line to pass the source parameter
        } else if (destination->right == nullptr) { //  line to check if the right node is null
            destination->right = source; //  line to pass the source parameter
        }
    }

    FileDirectoryTree() : root(nullptr) {}

    void createDirectory(string name, string parentPath) {
        root = createDirectory(root, name, parentPath);
    }

    void createFile(string name, string type, string parentPath) {
        root = createFile(root, name, type, parentPath);
    }

    void listTree() {
        listTree(root);
    }

    void deleteNode(string name, string parentPath) {
        root = deleteNode(root, name, "/" + rootName + parentPath);
    }
    

    void setRootName(const string& name) {
        rootName = name; // Modify this line to set rootName
        root = createNode(name, "/" + name, "");
    }
    void searchFile(TreeNode* node, const string& fileName, TreeNode*& fileNode) {
        if (node == nullptr) {
            return;
        }

        if (node->name == fileName && !node->type.empty()) { //  line to check if the node is a file
            cout << "File found at path: " << node->path << "\n";
            fileNode = node;  // Update the fileNode parameter
            return;
        }

        searchFile(node->left, fileName, fileNode); //  line to pass the fileNode parameter
        searchFile(node->right, fileName, fileNode); //  line to pass the fileNode parameter
    }

    bool searchDirectory(TreeNode* node, const string& dirName) {
        if (node == nullptr) {
            return false;
        }

        if (node->name == dirName && node->type.empty()) { //  line to check if the node is a directory
            return true;
        }

        return searchDirectory(node->left, dirName) || searchDirectory(node->right, dirName); //  line to pass the dirName parameter
    }

    void copyFile() {
        string fileName;
        cout << "Enter the name of the file to copy: ";
        cin >> fileName;

        // Initialize fileNode to nullptr
        TreeNode* fileNode = nullptr;

        // Call the searchFile function with the fileNode parameter
        searchFile(root, fileName, fileNode);

        if (fileNode == nullptr) { //  line to check if the fileNode is null
            cout << "File " << fileName << " not found!\n";
            return;
        }

        string destDirName;
        cout << "Enter the destination directory name: ";
        cin >> destDirName;

        // Search for the destination directory
        TreeNode* destNode = findNode(root, destDirName);

        if (destNode == nullptr || !destNode->type.empty()) { //  line to check if the node is a file
            cout << "Directory " << destDirName << " not found!\n";
            return;
        }

        // Check if the file with the same name already exists in the destination directory
        string destFilePath = destNode->path + "/" + fileName;
        if (findNode(root, destFilePath) != nullptr) { //  line to pass the destFilePath parameter
            cout << "File with the same name already exists in the destination directory!\n";
            return;
        }

        // Check if there is enough space in the destination directory (assuming left and right are available)
        if (destNode->left != nullptr && destNode->right != nullptr) { //  line to check if the left and right node is null
            cout << "Destination directory is full! Cannot copy file.\n";
            return;
        }

        // Copy the file node to the destination directory
        createFile(fileName, fileNode->type, destNode->path + "/" + fileName);
        cout << "File copied successfully.\n";
    }
    void deleteDir(TreeNode* node, TreeNode* parent) {
        if (node == nullptr) {
            return;
        }

        if (parent != nullptr) { //  line to check if the parent is not null
            if (parent->left == node) { //  line to check if the left node is null
                parent->left = nullptr; //  line to set the left node to null
            } else if (parent->right == node) { //  line to check if the right node is null
                parent->right = nullptr; //  line to set the right node to null
            }
        }

        delete node;
    }


    void mergeWith(TreeNode* sourceA, TreeNode* sourceB, TreeNode* dest) {
        if (sourceA == nullptr || sourceB == nullptr || dest == nullptr) { //  line to check if the sourceA, sourceB and dest is null
            cout << "Invalid sources or destination.\n";
            return;
        }

        // Check if the destination directory is full
        if (dest->left != nullptr && dest->right != nullptr) { //  line to check if the left and right node is null
            cout << "Destination directory is full.\n";
            cout << "1. Replace\n";
            cout << "2. Abort\n";
            cout << "3. Rename destination to: ----\n";

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    // Replace the destination directory
                    dest->left = nullptr; //  line to set the left node to null
                    dest->right = nullptr; //  line to set the right node to null

                    TreeNode* newDir = createNode(dest->name, dest->path, "");  // Create a new directory with the same name
                    move(sourceA, newDir); //  line to pass the newDir parameter
                    move(sourceB, newDir); //  line to pass the newDir parameter    
                    deleteDir(dest, nullptr); //  line to pass the nullptr parameter
                    break;
                }
                case 2: {
                    // Abort the merging process
                    cout << "Merging aborted.\n";
                    break;
                }
                case 3: {
                    // Rename the destination directory
                    string newName;
                    cout << "Enter the new name for the destination directory: ";
                    cin >> newName;

                    // Construct a new parent directory with the specified name
                    TreeNode* newDir = createNode(newName, dest->path.substr(0, dest->path.find_last_of('/')) + "/" + newName, ""); //  line to set the path
                    move(sourceA, newDir); //  line to pass the newDir parameter
                    move(sourceB, newDir); //  line to pass the newDir parameter 
                    deleteDir(dest, nullptr); //  line to pass the nullptr parameter
                    cout << "Destination directory renamed successfully.\n"; 
                    break;
                }
                default:
                    cout << "Invalid choice. Merging aborted.\n";
            }
        } else {
            // Merge the source directories into the destination directory
            move(sourceA, dest); //  line to pass the dest parameter
            move(sourceB, dest); //  line to pass the dest parameter
            cout << "Directories merged successfully.\n";
        }
    }

    void mergeDirectories(FileDirectoryTree& fileSystem) {
        string destDirPath, sourceDirPathA, sourceDirPathB;

        // Get the destination directory path from the user
        cout << "Enter the path of the destination directory: ";
        cin >> destDirPath;

        // Get the paths of the source directories from the user
        cout << "Enter the path of the first source directory: ";
        cin >> sourceDirPathA;
        cout << "Enter the path of the second source directory: ";
        cin >> sourceDirPathB;

        // Search for the destination directory node
        TreeNode* destNode = fileSystem.findNode(fileSystem.root, destDirPath); // line to pass the destDirPath parameter

        if (destNode == nullptr || !destNode->type.empty()) { //  line to check if the node is a file
            cout << "Directory " << destDirPath << " not found!\n";
            return;
        }

        // Search for the source directory nodes
        TreeNode* sourceNodeA = fileSystem.findNode(fileSystem.root, sourceDirPathA); 
        TreeNode* sourceNodeB = fileSystem.findNode(fileSystem.root, sourceDirPathB);

        if (sourceNodeA == nullptr || sourceNodeB == nullptr) { //  line to check if the sourceNodeA and sourceNodeB is null
            cout << "One or both source directories not found!\n";
            return;
        }

        // Perform the merge operation
        fileSystem.mergeWith(sourceNodeA, sourceNodeB, destNode); //  line to pass the destNode parameter
    }

    TreeNode* getRoot() {
        return root;
    }

    int calculateTreeHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftSubtreeHeight = calculateTreeHeight(node->left); //  line to pass the node->left parameter
        int rightSubtreeHeight = calculateTreeHeight(node->right); //  line to pass the node->right parameter

        return max(leftSubtreeHeight, rightSubtreeHeight) + 1; //  line to return the max height
    }

    void processNodeAtLevel(TreeNode* node, int level, ofstream& file, bool exportMode) {
        if (node == nullptr) {
            return;
        }

        if (level == 1 && (!exportMode || (exportMode && node->type != "DELETED"))) { //  line to check if the node is not null
            file << node->name << " " << node->path  << "\n";
        } else if (level > 1) { //  line to check if the level is greater than 1
            processNodeAtLevel(node->left, level - 1, file, exportMode); //  line to pass the level - 1 parameter
            processNodeAtLevel(node->right, level - 1, file, exportMode); //  line to pass the level - 1 parameter
        }
    }

    void exportTreeToFile(TreeNode* root, ofstream& file) {
        int treeHeight = calculateTreeHeight(root); //  line to pass the root parameter

        for (int level = 1; level <= treeHeight; level++) { //  line to check if the level is less than or equal to treeHeight
            processNodeAtLevel(root, level, file, true); //  line to pass the root parameter
        }
    }

    void importTreeFromFile(TreeNode* root, ifstream& file) {
        string name, path, type;

        // Read the first line to skip the root directory entry
        file >> name >> path >> type;

        while (file >> name >> path >> type) { // line to check if the file is not null
            if (type != "DELETED") {
                createFile(root, name, type, path);
            }
        }

        // Display the imported tree without the root directory entry
        listTree(root);
    }

};


