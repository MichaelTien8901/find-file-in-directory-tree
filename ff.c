#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_MODULE_NAME_SIZE 1000

/**
 * @brief Find file path in directory tree
 *        Find out if the file exists under the directory tree.         
 * 
 * @param start_folder path of starting folder
 * @param filename the file to search, exclude the path
 * @param found_file_path output of the found file path
 * @param max_level how many depth level to search, value start from 1
 * @retval  1 success, file found, and found_file_path has the file path.
 * @retval  0 failed 
 *
 */
static int find_file_in_directory_tree(char *start_folder, char *filename, char *found_file_path, int max_level) 
{
	struct dirent *entry;
	char entry_path[MAX_MODULE_NAME_SIZE];
	DIR *dp;
	struct stat sb;
	int result = 0;
	if ( max_level == 0) return 0;
	dp = opendir(start_folder);
	if ( dp == NULL) {
		return 0;
	}
	while(entry = readdir(dp)) {
		if ( entry->d_name[0] == '.') continue; // eliminate current, upper folder, and hidden folder
		if ( snprintf(entry_path, MAX_MODULE_NAME_SIZE, "%s/%s",start_folder, entry->d_name ) > MAX_MODULE_NAME_SIZE ) {
			break;
		}
		if ( stat( entry_path, &sb) == 0) {
			if ( S_ISDIR( sb.st_mode)) {
				if (find_file_in_directory_tree( entry_path, filename, found_file_path, max_level-1)) {
					result = 1;
					break;
				}
			} else {
				if ( strncmp( entry->d_name, filename, MAX_MODULE_NAME_SIZE) == 0) {
					strncpy( found_file_path, entry_path, MAX_MODULE_NAME_SIZE);
					result = 1;
					break;
				}
			}
		} else break;
	}
	closedir(dp);
	return result;
}

void usage(char *argv[])
{
	printf( "%s: Find file under directory tree.\n", argv[0]);
	printf( "Usage %s start_folder file_name max_level\n", argv[0]);
}
int main(int argc, char *argv[])
{
	char found_path[MAX_MODULE_NAME_SIZE];
	if ( argc != 4) {
		usage(argv);
		return 0;
	}
	int level = atoi( argv[3]);
	if ( find_file_in_directory_tree( argv[1], argv[2], found_path, level)) {
		printf( "found file path = %s\n", found_path);
	}
}
