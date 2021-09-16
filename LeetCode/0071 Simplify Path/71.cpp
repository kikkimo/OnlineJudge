class Solution {
public:
  string parentPath(string &path) {
    string str = path.substr(0, path.rfind('/'));
    return str;
  }
  string simplifyPath(string path) {
    int len = path.length();
    if (0 == len)
      return "/";
    string pathCov = "/";
    for (int i = 0; i < len; ++i) {
      if (path[i] != '/') {
        pathCov += path[i];
      } else {
        if (pathCov[pathCov.length() - 1] == '/')
          continue;
        else
          pathCov += '/';
      }
    }
    if (pathCov[pathCov.length() - 1] != '/') {
      pathCov += '/';
    }
    len = pathCov.length();
    string res;
    bool isPath = false;
    string folder{};
    string seperator{};
    for (int i = 0; i < len; ++i) {
      char ch = pathCov[i];
      if (ch != '.' && ch != '/') {
        if (isPath == false) {
          isPath = true;
          if (!seperator.empty()) {
            int pos = -1;
            for (int j = 0; j < seperator.length(); ++j) {
              if (seperator[j] != '/') {
                pos = j;
                break;
              }
            }
            if (pos != -1) {
              seperator = seperator.substr(pos, seperator.length() - pos);
              folder += seperator;
            }
            seperator = {};
          }
        }
        folder += ch;
      } else {
        if (isPath) {
          if (ch == '.') {
            folder += ch;
            continue;
          }
          res += '/';
          res += folder;
          folder = {};
          isPath = false;
          seperator += ch;
        } else {
          seperator += ch;
          if (seperator == "/./") {
            seperator = {"/"};
            continue;
          }
          if (seperator == "/../") {
            res = parentPath(res);
            seperator = {"/"};
            continue;
          }
        }
      }
    }
    if (!folder.empty()) {
      res += '/';
      res += folder;
    }
    if (!seperator.empty()) {
      res += seperator;
    }
    if (res[res.length() - 1] == '/') {
      res = res.substr(0, res.length() - 1);
    }
    if (res == "")
      res = "/";
    return res;
  }
};