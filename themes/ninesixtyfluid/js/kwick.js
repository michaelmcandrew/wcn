jQuery(function ($) {
    var animating = false;
    $("#kwick .kwick")
        .bind("mouseenter", function(e) {
            if (animating) return false;

            animating == true;
            $("#kwick .kwick").not(this).animate({ "width": 125 }, 200);
            $(this).animate({ "width": 485 }, 200, function() {
                animating = false;
            });
        });

    $("#kwick").bind("mouseleave", function(e) {
        $(".kwick", this).animate({ "width": 215 }, 200);
    });
});
