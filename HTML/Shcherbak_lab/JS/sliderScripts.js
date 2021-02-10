
let Slide = 0;
let numberSlides = 4;

function slider() {
    let slider = document.getElementById("Slider");
    for (let i = 0; i < numberSlides; ++i) {
        slider.children[i].style.display = "none";
    }
    display(-1, Slide);
    setTimer();
}

function display(oldSlide, newSlide) {
    let slider = document.getElementById("Slider");
    if(oldSlide !== -1){
        slider.children[oldSlide].style.display = "none";
        slider.children[oldSlide].classList.remove("hiddenImage");
        slider.children[oldSlide].classList.add("showImage");
    }
    slider.children[newSlide].classList.remove("showImage");
    slider.children[newSlide].classList.add("hiddenImage");
    slider.children[newSlide].style.display = "block";

}

function swipe(isRight) {
    let OldSlide = Slide;
    Slide += (isRight ? 1 : -1);
    Slide = (Slide + numberSlides) % numberSlides;
    display(OldSlide, Slide);
    console.log("Swiping " + (isRight ? "right!" : "left!"));
}

function setTimer() {
    console.log("Timer is set!")
    setInterval(swipe, 4000, 1);
}

