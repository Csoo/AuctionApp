import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    function wordfilter(str){
        var fs = require('fs');
        var words = fs.readFileSync('words.txt').toString().split("\r\n");
        var isInclude = words.some(word => str.includes(word));
        return isInclude;
    }
}
