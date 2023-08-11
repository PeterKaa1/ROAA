function downloadAll(version) {
	const links = document.querySelectorAll(`a[href^="versions/${version}"]`);
	links.forEach(link => {
		link.click();
	});
}
