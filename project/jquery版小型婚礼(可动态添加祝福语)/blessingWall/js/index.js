/**
 * User: wei ya
 * Date: 14-6-12
 * Time: 下午8:08
 * 小型婚礼
 */
$(function(){
    var $firstHorn = $(".first-horn"), /* 场景一左边喇叭 */
        $firstTxt = $(".first-txt"), /* 场景一文字div */
        firstTxtWidth = $firstTxt.width(), /* 文字div的宽度 */
        $secondBox = $(".second-box"), /* 场景二box */
        $secondPeople = $(".second-people"), /* 场景二左边人物 */
        $secondTxt = $(".second-txt"), /* 场景二右边文字 */
        $threeBox = $(".three-box"), /* 场景三box */
        $threeImg = $(".three-img"), /* 场景三图片 */
        $foreBox = $(".fore-box"), /* 场景四box */
        $foreImg = $(".fore-img"), /* 场景四图片 */
        $fiveBox = $(".five-box"), /* 场景五box */
        $fiveImg = $(".five-img"), /* 场景五中间图片 */
        $uEnter = $(".u-enter"), /* 进入婚礼按钮 */
        $sixBox = $(".six-box"), /* 场景六box */
        $sixDiv = $sixBox.find("div"), /* 场景六里面小块div */
        sixDivWidth = $sixDiv.width(), /* 场景六里面小块div的宽度 */
        sixDivHeight = $sixDiv.height(), /* 场景六里面小块div的高度 */
        sixBoxWidth = $sixBox.width(), /* 场景六宽度 */
        sixBoxHeight = $sixBox.height(),/* 场景六高度 */
        $sevenBox = $(".seven-box");

    /* 场景一 */
    $firstHorn.animate({left: 0},1000);
    $firstTxt.animate({left: "435px"},function(){
        $firstTxt.fadeIn(1000);
        showTxt($firstTxt.find("div:eq(0)")); /* 显示第一行文字 */
        setTimeout(function(){showTxt($firstTxt.find("div:eq(1)"));},3000); /* 显示第二行文字 */
        setTimeout(scene2,7000); /* 进入场景二 */
    });

    /* 显示文字 */
    function showTxt($obj){
        for(var i = 0; i < 8; i++){
            (function(){
                $obj.animate({width: firstTxtWidth*(i+1)+"px"}); /* 根据i值，width逐渐变大 */
            })(i)
        }
    }

    /* 场景二 */
    function scene2(){
        $firstTxt.fadeOut();
        $firstHorn.animate({left: "-422px"},function(){
            $secondBox.show();
            $secondPeople.animate({left: "0"});
            $secondTxt.animate({left: "230px"},function(){
                $secondTxt.fadeIn(1000);
                setTimeout(scene3,2000); /* 进入场景三 */
            });
        });
    }

    /* 场景三 */
    function scene3(){
        $secondBox.hide();
        $threeBox.fadeIn();
        for(var i = 0; i < 6; i++){ /* 控制图片跳转频率 */
            if(i==0){
                $threeImg.css({left:0,top:0});
            }else if(i%2==0){
                $threeImg.animate({left: 40*i+"px",top: 30*i+"px"},80*(6-i));
            }else{
                $threeImg.animate({left: 40*i+"px",top: "200px"},80*(6-i));
            }
        }
        setTimeout(scene4,2500); /* 进入场景四 */
    }

    /* 场景四 */
    function scene4(){
        $threeBox.hide();
        $foreBox.fadeIn();
        $foreImg.animate({top: "80px"},1000);
        setTimeout(scene5,2500); /* 进入场景五 */
    }

    /* 场景五 */
    function scene5(){
        $foreImg.animate({left: "960px"},function(){
            $fiveBox.fadeIn();
            $fiveBox.find("img").css({"transform": "scale(1)"});
            $uEnter.click(function(){
                $fiveBox.hide();
                setTimeout(scene6,400); /* 进入第六场景 */
            })
        });
    }

    /* 场景六 */
    var colCount = 4, /* 多少列 */
        rowCount = 4; /* 多少行 */
    function scene6(){
        $sixBox.fadeIn();
        /* 聚合 */
        $sixDiv.each(function(){
            var _index = $(this).index(),
                col = _index%colCount, /* 第几列 */
                row = Math.floor(_index/rowCount), /* 第几行 */
                cssLeft = sixBoxWidth/2 - colCount/2*sixDivWidth + col*sixDivWidth, /* left的值 */
                cssTop = sixBoxHeight/2 - rowCount/2*sixDivHeight + row*sixDivHeight, /* top的值 */
                divLeft = -col*sixDivWidth, /* 背景定位的宽度 */
                divTop = -row*sixDivHeight; /* 背景定位的高度 */
            $(this).css({"left": cssLeft,"top": cssTop, "background-position": divLeft+"px "+divTop+"px"}); /* 先设置成为聚合，定位好背景图片 */
            setTimeout(scatter,1600); /* 调用散开 */
        })
        setTimeout(scene7,3000); /* 进入第七场景 */
    }
    /* 散开 */
    function scatter(){
        $sixDiv.each(function(){
            var _index = $(this).index(),
                col = _index%colCount, /* 第几列 */
                row = Math.floor(_index/rowCount), /* 第几行 */
                cssLeft = (col-1)*(sixBoxWidth+sixDivWidth)- sixDivWidth, /* 我这里的水平间距大小为盒子大小加上它自身的宽度 */
                cssTop = (row-1)*(sixBoxHeight+sixDivHeight)- sixDivWidth; /* 我这里的水平间距大小为盒子大小加上它自身的宽度 */
                $(this).animate({"left": cssLeft,"top": cssTop},1200);
        })
    }


    /* 场景七 */
    var $sevenDiv = $(".seven-content div"),
        $clickMe = $(".clickMe"),
        /* 送上祝福 */
        $mask = $(".mask"),
        $popBox = $(".pop-box"),
        $write = $("#write"),
        $uSure = $("#uSure"),
        $sevenContent = $(".seven-content");

    function scene7(){
        $sixBox.hide();
        $sevenBox.fadeIn(1000);
        $sevenDiv.each(function(){
            defineSevenDiv($(this));
        })

        function defineSevenDiv($own){
            var _obj = defineRandom();
            $own.css({"transform":"rotate("+_obj.rotate+"deg)"}); /* 设置随机旋转值 */
            $own.animate({left: _obj.left+"px",top: _obj.top+"px"}); /* 随机排布 */
        }

        /* 定义随机left，top和旋转值 */
        function defineRandom(){
            var randomLeft = Math.floor(680*(Math.random())) + 30, /* 图片left值 */
                randomTop =  Math.floor(400*Math.random()) + 30, /* 图片top值 */
                randomRotate = 20 - Math.floor(40*Math.random()); /* 图片旋转角度 */
            return {
                left: randomLeft,
                top: randomTop,
                rotate:randomRotate
            }
        }

        /* 拖动祝福卡片 */
        draggableNote();
        /* 拖动图片 */
        function draggableNote(){
            $(".seven-content div").draggable({
                containment: $sevenContent,
                zIndex: 2700,
                start: function(){
                    $(this).css({"transform":"rotate(0deg)","cursor": "crosshair"}); /* 开始拖动图片旋转为0，鼠标样式改变 */
                },
                stop: function(){
                    var _obj = defineRandom();
                    $(this).css({"transform":"rotate("+_obj.rotate+"deg)","cursor": "pointer"}); /* 停止拖动，旋转为随机的 */
                }
            })
        }

        /* 点我送祝福 */
        $clickMe.click(function(){
            $write.val("送上您的祝福吧~");
            $mask.fadeIn();
            $popBox.animate({top: "50%"});
        })

        /* 获取焦点时 */
        $write.focus(function(){
            var _val = $(this).val();
            if(_val == "送上您的祝福吧~"){
                $(this).val("");
            }
        })
        /* 丢失焦点时 */
        $write.blur(function(){
            var _val = $(this).val();
            if(_val.length == 0){
                $(this).val("送上您的祝福吧~");
            }
        })

        /* 点击确定 */
        $uSure.click(function(){
            var _writeVal = $write.val();
            var _randomNum = Math.ceil(Math.random()*6);
            if(_writeVal != "送上您的祝福吧~"){
                var _div = '<div class="note-'+_randomNum+'">'+_writeVal+'</div>';
                $sevenContent.append(_div); /* 如果输入祝福语，将此标签添加的尾部 */
                defineSevenDiv($sevenContent.find("div:last"));
                $popBox.animate({top: "-300px"},function(){
                    $mask.fadeOut();
                    draggableNote(); /* 可拖动卡片，给新添加的标签赋予拖动功能 */
                });
            }else{
                alert("请输入祝福语！");
            }
        })


    }




})
