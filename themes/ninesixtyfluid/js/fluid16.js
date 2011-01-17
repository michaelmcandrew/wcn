jQuery(function ($) {
    $("#loading").hide();

    var content = $("#ajax-content").hide();

    $("#toggle-ajax").bind("click", function(e) {
        if ( $(this).is(".hidden") ) {
            $("#ajax-content").empty();

            $("#loading").show();
            $("#ajax-content").load(
                "ajax-response.html",
                function() {
                    $("#loading").hide();
                    content.slideDown();
                });
        }
        else {
            content.slideUp();
        }

        if ($(this).hasClass('hidden')){
            $(this).removeClass('hidden').addClass('visible');
        }
        else {
            $(this).removeClass('visible').addClass('hidden');
        }

        return false;
    });

    var default_hide = {"grid": true,  "paragraphs": true };

    $.each(
        ["grid", "paragraphs", "blockquote", "list-items",
         "section-menu", "tables", "forms", "login-forms",
         "search", "articles", "accordian"],
        function() {
            var el = $("#" + (this == 'accordian' ? 'accordian-block' : this) );

            if (default_hide[this]) {
                el.hide();
                $("#toggle-" + this).addClass("hidden")
            }

            $("#toggle-" + this)
                .bind("click", function(e) {
                    if ($(this).hasClass('hidden')){
                        $(this).removeClass('hidden').addClass('visible');
                        el.slideDown();
                    }
                    else {
                        $(this).removeClass('visible').addClass('hidden');
                        el.slideUp();
                    }
                    return false;
                });
        }
    );
});
