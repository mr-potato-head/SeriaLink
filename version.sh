echo "/*" > src/version.h
echo "* Copyright (C) 2016 Guilhem GUYONNET" >> src/version.h
echo "*" >> src/version.h
echo "* This program is free software: you can redistribute it and/or modify" >> src/version.h
echo "* it under the terms of the GNU General Public License as published by" >> src/version.h
echo "* the Free Software Foundation, either version 3 of the License, or" >> src/version.h
echo "* (at your option) any later version." >> src/version.h
echo "*" >> src/version.h
echo "* This program is distributed in the hope that it will be useful," >> src/version.h
echo "* but WITHOUT ANY WARRANTY; without even the implied warranty of" >> src/version.h
echo "* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the" >> src/version.h
echo "* GNU General Public License for more details." >> src/version.h
echo "*" >> src/version.h
echo "* You should have received a copy of the GNU General Public License" >> src/version.h
echo "* along with this program. If not, see <http://www.gnu.org/licenses/>." >> src/version.h
echo "*" >> src/version.h
echo "*/" >> src/version.h
echo "" >> src/version.h
echo "#ifndef SRC_VERSION_H_" >> src/version.h
echo "#define SRC_VERSION_H_" >> src/version.h
echo "" >> src/version.h

RESULT=`git.exe describe --tags --long --dirty`
echo "#define VERSION \"$RESULT\"" >> src/version.h

echo "" >> src/version.h
echo "#endif  // SRC_VERSION_H_" >> src/version.h