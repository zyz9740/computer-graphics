var AudioContext = window.AudioContext || window.webkitAudioContext; //Cross browser variant.

var canvas, ctx;
var audioContext;
var file;
var fileContent;
var audioBufferSourceNode;
var analyser;

var loadFile = function() {
    var fileReader = new FileReader();
    fileReader.onload = function(e) {
        fileContent = e.target.result;
        decodecFile();
    }
    fileReader.readAsArrayBuffer(file);
}

var decodecFile = function() {
    audioContext.decodeAudioData(fileContent, function(buffer) {
        start(buffer);
    });
}

var start = function(buffer) {
    if(audioBufferSourceNode) {
        audioBufferSourceNode.stop();
    }

    audioBufferSourceNode = audioContext.createBufferSource();
    audioBufferSourceNode.connect(analyser);
    analyser.connect(audioContext.destination);
    audioBufferSourceNode.buffer = buffer;
    audioBufferSourceNode.start(0);
    showTip(false);
    window.requestAnimationFrame(render); //先判断是否已经调用一次
}

var showTip = function(show) {
    var tip = document.getElementById('tip');
    if (show) {
        tip.className = "show";
    } else {
        tip.className = "";
    }
}

// var render = function() {
//     ctx = canvas.getContext("2d");
//     ctx.strokeStyle = "#00d0ff";
//     ctx.lineWidth = 2;
//     ctx.clearRect(0, 0, canvas.width, canvas.height);

//     var dataArray = new Uint8Array(analyser.frequencyBinCount);
//     analyser.getByteFrequencyData(dataArray);
//     var step = Math.round(dataArray.length / 60);

//     for (var i = 0; i < 40; i++) {
//         var energy = (dataArray[step * i] / 256.0) * 50;
//         for (var j = 0; j < energy; j++) {
//             ctx.beginPath();
//             ctx.moveTo(20 * i + 2, 200 + 4 * j);
//             ctx.lineTo(20 * (i + 1) - 2, 200 + 4 * j);
//             ctx.stroke();
//             ctx.beginPath();
//             ctx.moveTo(20 * i + 2, 200 - 4 * j);
//             ctx.lineTo(20 * (i + 1) - 2, 200 - 4 * j);
//             ctx.stroke();
//         }
//         ctx.beginPath();
//         ctx.moveTo(20 * i + 2, 200);
//         ctx.lineTo(20 * (i + 1) - 2, 200);
//         ctx.stroke();
//     }

//     window.requestAnimationFrame(render);
// }
    function render() {
        var PI = Math.PI;
        var ctx = canvas.getContext('2d');
        var cwidth = canvas.width;
        var cheight = canvas.height;
        /* 参数配置 */
        var radius = 150;           // 环形半径
        var minHeight = 2;          // 最小高度
        var meterWidth = 5;         // 方块宽度
        var meterNum = 120;         // 方块数量
        /* 线性颜色渐变 */
        var gradient = ctx.createLinearGradient(0, -radius, 0, -cwidth/2);
        gradient.addColorStop(0, '#0f0');
        gradient.addColorStop(0.5, '#ff0');
        gradient.addColorStop(1, '#f00');
        ctx.fillStyle = gradient;
        /* 采样 */
        var array = new Uint8Array(analyser.frequencyBinCount);
        analyser.getByteFrequencyData(array);
        var step = Math.round(array.length / meterNum);

        ctx.clearRect(0, 0, cwidth, cheight);
        ctx.save();
        ctx.translate(cwidth/2,cheight/2);          //画布中心映射到圆心
        for (var i = 0; i < meterNum; i++) {
            var value = array[i * step];
            var radio = i
            var meterHeight = value*(cheight/2 - radius)/256 || minHeight;
            ctx.rotate( 2*PI/meterNum );
            /* 
            (-width/2, -r-height)
                |
                *--*
                |  |
                |  |
                |  |
                |  |
                |  |
                |  |
                *--*
            */
            ctx.fillRect( -meterWidth/2 , - radius - meterHeight , meterWidth, meterHeight);
        }
        ctx.restore();
        requestAnimationFrame(render);
    }

window.onload = function() {
    audioContext = new AudioContext();
    analyser = audioContext.createAnalyser();
    analyser.fftSize = 256;

    var fileChooser = document.getElementById('fileChooser');
    fileChooser.onchange = function() {
        if (fileChooser.files[0]) {
            file = fileChooser.files[0];
            showTip(true);
            loadFile();
        }
    }

    canvas = document.getElementById('visualizer');
}