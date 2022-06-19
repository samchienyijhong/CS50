// Arrow blink
function blinkr() {
    let arrowr = document.querySelector(".bx-chevron-right");
    if (arrowr.style.visibility === "hidden") {
        arrowr.style.visibility = "visible";
    }
    else {
        arrowr.style.visibility = "hidden";
    }
}

function blinkl() {
    let arrowl = document.querySelector(".bx-chevron-left");
    if (arrowl.style.visibility === "hidden") {
        arrowl.style.visibility = "visible";
    }
    else {
        arrowl.style.visibility = "hidden";
    }
}

window.setInterval(blinkr, 600);
window.setInterval(blinkl, 600);

// Scroll to top
let rootElement = document.documentElement;

function scrollToTop() {
    rootElement.scrollTo({
        top: 0,
        behavior: "smooth"
    });
}

document.addEventListener("DOMContentLoaded", (event) => {
    let scrollToTopBtn = document.querySelector("#scroll-to-top-btn");
    scrollToTopBtn.addEventListener("click", scrollToTop);

    // Current year
    let year = document.querySelector(".year");
    year.innerHTML = new Date().getFullYear();
})
